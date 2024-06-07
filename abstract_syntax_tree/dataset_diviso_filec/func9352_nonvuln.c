TEST_F(RouterTest, UpstreamPerTryTimeout) {
  NiceMock<Http::MockRequestEncoder> encoder;
  Http::ResponseDecoder* response_decoder = nullptr;
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke(
          [&](Http::ResponseDecoder& decoder,
              Http::ConnectionPool::Callbacks& callbacks) -> Http::ConnectionPool::Cancellable* {
            response_decoder = &decoder;
            callbacks.onPoolReady(encoder, cm_.thread_local_cluster_.conn_pool_.host_,
                                  upstream_stream_info_, Http::Protocol::Http10);
            return nullptr;
          }));
  EXPECT_CALL(callbacks_.stream_info_, onUpstreamHostSelected(_))
      .WillOnce(Invoke([&](const Upstream::HostDescriptionConstSharedPtr host) -> void {
        EXPECT_EQ(host_address_, host->address());
      }));

  Http::TestRequestHeaderMapImpl headers{{"STR"},
                                         {"STR"}};
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, false);

  
  
  expectPerTryTimerCreate();
  expectResponseTimerCreate();

  Buffer::OwnedImpl data;
  router_.decodeData(data, true);
  EXPECT_EQ(1U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  EXPECT_CALL(callbacks_.stream_info_,
              setResponseFlag(StreamInfo::ResponseFlag::UpstreamRequestTimeout));
  EXPECT_CALL(encoder.stream_, resetStream(Http::StreamResetReason::LocalReset));
  Http::TestResponseHeaderMapImpl response_headers{
      {"STR"}};
  EXPECT_CALL(callbacks_, encodeHeaders_(HeaderMapEqualRef(&response_headers), false));
  EXPECT_CALL(callbacks_, encodeData(_, true));
  EXPECT_CALL(
      cm_.thread_local_cluster_.conn_pool_.host_->outlier_detector_,
      putResult(Upstream::Outlier::Result::LocalOriginTimeout, absl::optional<uint64_t>(504)));
  per_try_timeout_->invokeCallback();

  EXPECT_EQ(1U, cm_.thread_local_cluster_.cluster_.info_->stats_store_
                    .counter("STR")
                    .value());
  EXPECT_EQ(1UL, cm_.thread_local_cluster_.conn_pool_.host_->stats().rq_timeout_.value());
  EXPECT_TRUE(verifyHostUpstreamStats(0, 1));
}