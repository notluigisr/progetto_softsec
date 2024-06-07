TEST_F(RouterTest, RetryTimeoutDuringRetryDelay) {
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

  
  EXPECT_CALL(callbacks_.stream_info_,
              setResponseFlag(StreamInfo::ResponseFlag::UpstreamRequestTimeout));

  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_, putResponseTime(_))
      .Times(0);
  Http::TestResponseHeaderMapImpl response_headers{
      {"STR"}};
  EXPECT_CALL(callbacks_, encodeHeaders_(HeaderMapEqualRef(&response_headers), false));
  EXPECT_CALL(callbacks_, encodeData(_, true));
  response_timeout_->invokeCallback();
  EXPECT_TRUE(verifyHostUpstreamStats(0, 1));
}