TEST_F(RouterTest, GrpcOk) {
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

  Http::TestRequestHeaderMapImpl headers{{"STR"},
                                         {"STR"}};
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, true);
  EXPECT_EQ(1U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  EXPECT_CALL(callbacks_.dispatcher_, pushTrackedObject(_));
  EXPECT_CALL(callbacks_.dispatcher_, popTrackedObject(_));
  Http::ResponseHeaderMapPtr response_headers(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
              putHttpResponseCode(200));
  response_decoder->decodeHeaders(std::move(response_headers), false);
  EXPECT_TRUE(verifyHostUpstreamStats(0, 0));

  EXPECT_CALL(callbacks_.dispatcher_, pushTrackedObject(_));
  EXPECT_CALL(callbacks_.dispatcher_, popTrackedObject(_));
  Http::ResponseTrailerMapPtr response_trailers(
      new Http::TestResponseTrailerMapImpl{{"STR"}});
  response_decoder->decodeTrailers(std::move(response_trailers));
  EXPECT_TRUE(verifyHostUpstreamStats(1, 0));
}