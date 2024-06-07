TEST_F(RouterTest, RetryUpstream5xxNotComplete) {
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
  router_.decodeHeaders(headers, false);

  Buffer::InstancePtr body_data(new Buffer::OwnedImpl("STR"));
  EXPECT_CALL(*router_.retry_state_, enabled()).WillOnce(Return(true));
  EXPECT_CALL(callbacks_, addDecodedData(_, true));
  EXPECT_EQ(Http::FilterDataStatus::StopIterationNoBuffer, router_.decodeData(*body_data, false));

  Http::TestRequestTrailerMapImpl trailers{{"STR"}};
  router_.decodeTrailers(trailers);
  EXPECT_EQ(1U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  
  router_.retry_state_->expectHeadersRetry();
  Http::ResponseHeaderMapPtr response_headers1(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  EXPECT_CALL(encoder1.stream_, resetStream(Http::StreamResetReason::LocalReset));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
              putHttpResponseCode(503));
  response_decoder->decodeHeaders(std::move(response_headers1), false);
  EXPECT_TRUE(verifyHostUpstreamStats(0, 1));

  
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
  ON_CALL(callbacks_, decodingBuffer()).WillByDefault(Return(body_data.get()));
  EXPECT_CALL(encoder2, encodeHeaders(_, false));
  EXPECT_CALL(encoder2, encodeData(_, false));
  EXPECT_CALL(encoder2, encodeTrailers(_));
  router_.retry_state_->callback_();
  EXPECT_EQ(2U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  
  EXPECT_CALL(*router_.retry_state_, shouldRetryHeaders(_, _)).WillOnce(Return(RetryStatus::No));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
              putHttpResponseCode(200));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_, putResponseTime(_));
  EXPECT_CALL(
      cm_.thread_local_cluster_.conn_pool_.host_->health_checker_,
      setUnhealthy(Upstream::HealthCheckHostMonitor::UnhealthyType::ImmediateHealthCheckFail));
  Http::ResponseHeaderMapPtr response_headers2(new Http::TestResponseHeaderMapImpl{
      {"STR"}});
  response_decoder->decodeHeaders(std::move(response_headers2), true);
  EXPECT_TRUE(verifyHostUpstreamStats(1, 1));

  EXPECT_EQ(1U,
            cm_.thread_local_cluster_.cluster_.info_->stats_store_.counter("STR")
                .value());
  EXPECT_EQ(
      1U,
      cm_.thread_local_cluster_.cluster_.info_->stats_store_.counter("STR").value());
  EXPECT_EQ(1U, cm_.thread_local_cluster_.cluster_.info_->stats_store_
                    .counter("STR")
                    .value());
  EXPECT_EQ(1U, cm_.thread_local_cluster_.cluster_.info_->stats_store_
                    .counter("STR")
                    .value());
}