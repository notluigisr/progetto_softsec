TEST_F(RouterTest, EnvoyAttemptCountInResponseWithRetries) {
  setIncludeAttemptCountInResponse(true);

  NiceMock<Http::MockRequestEncoder> encoder1;
  Http::ResponseDecoder* response_decoder = nullptr;
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke(
          [&](Http::ResponseDecoder& decoder,
              Http::ConnectionPool::Callbacks& callbacks) -> Http::ConnectionPool::Cancellable* {
            response_decoder = &decoder;
            callbacks.onPoolReady(encoder1, cm_.thread_local_cluster_.conn_pool_.host_,
                                  upstream_stream_info_, Http::Protocol::Http10);
            return nullptr;
          }));
  expectResponseTimerCreate();

  Http::TestRequestHeaderMapImpl headers{{"STR"}};
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, true);
  EXPECT_EQ(1U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  
  router_.retry_state_->expectHeadersRetry();
  Http::ResponseHeaderMapPtr response_headers1(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
              putHttpResponseCode(503));
  response_decoder->decodeHeaders(std::move(response_headers1), true);
  EXPECT_TRUE(verifyHostUpstreamStats(0, 1));

  
  EXPECT_CALL(encoder1.stream_, resetStream(_)).Times(0);
  NiceMock<Http::MockRequestEncoder> encoder2;
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke(
          [&](Http::ResponseDecoder& decoder,
              Http::ConnectionPool::Callbacks& callbacks) -> Http::ConnectionPool::Cancellable* {
            response_decoder = &decoder;
            callbacks.onPoolReady(encoder2, cm_.thread_local_cluster_.conn_pool_.host_,
                                  upstream_stream_info_, Http::Protocol::Http10);
            return nullptr;
          }));
  router_.retry_state_->callback_();
  EXPECT_EQ(2U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  
  EXPECT_CALL(*router_.retry_state_, shouldRetryHeaders(_, _)).WillOnce(Return(RetryStatus::No));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->health_checker_, setUnhealthy(_))
      .Times(0);
  Http::ResponseHeaderMapPtr response_headers2(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
              putHttpResponseCode(200));
  EXPECT_CALL(callbacks_, encodeHeaders_(_, true))
      .WillOnce(Invoke([](Http::ResponseHeaderMap& headers, bool) {
        
        EXPECT_EQ(2, atoi(std::string(headers.getEnvoyAttemptCountValue()).c_str()));
      }));
  response_decoder->decodeHeaders(std::move(response_headers2), true);
  EXPECT_TRUE(verifyHostUpstreamStats(1, 1));
}