TEST_F(RouterTest, MaxStreamDurationWhenDownstreamAlreadyStartedWithoutRetryPolicy) {
  NiceMock<Http::MockRequestEncoder> encoder1;
  Http::ResponseDecoder* response_decoder = nullptr;
  setUpstreamMaxStreamDuration(500);
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke(
          [&](Http::ResponseDecoder& decoder,
              Http::ConnectionPool::Callbacks& callbacks) -> Http::ConnectionPool::Cancellable* {
            response_decoder = &decoder;
            callbacks.onPoolReady(encoder1, cm_.thread_local_cluster_.conn_pool_.host_,
                                  upstream_stream_info_, Http::Protocol::Http10);
            return nullptr;
          }));
  expectMaxStreamDurationTimerCreate();

  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, false);
  Http::ResponseHeaderMapPtr response_headers(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  response_decoder->decodeHeaders(std::move(response_headers), false);
  max_stream_duration_timer_->invokeCallback();

  router_.onDestroy();
  EXPECT_TRUE(verifyHostUpstreamStats(1, 0));
}