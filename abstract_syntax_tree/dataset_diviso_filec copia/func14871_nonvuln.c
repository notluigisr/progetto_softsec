TEST_F(RouterTest, UpstreamPerTryIdleTimeoutSuccess) {
  InSequence s;

  callbacks_.route_->route_entry_.retry_policy_.per_try_idle_timeout_ =
      std::chrono::milliseconds(3000);

  NiceMock<Http::MockRequestEncoder> encoder;
  Http::ResponseDecoder* response_decoder = nullptr;
  Http::ConnectionPool::Callbacks* pool_callbacks;

  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke(
          [&](Http::ResponseDecoder& decoder,
              Http::ConnectionPool::Callbacks& callbacks) -> Http::ConnectionPool::Cancellable* {
            response_decoder = &decoder;
            pool_callbacks = &callbacks;
            return nullptr;
          }));

  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, false);

  response_timeout_ = new Event::MockTimer(&callbacks_.dispatcher_);
  EXPECT_CALL(*response_timeout_, enableTimer(_, _));

  Buffer::OwnedImpl data;
  router_.decodeData(data, true);

  EXPECT_CALL(callbacks_.stream_info_, onUpstreamHostSelected(_))
      .WillOnce(Invoke([&](const Upstream::HostDescriptionConstSharedPtr host) -> void {
        EXPECT_EQ(host_address_, host->address());
      }));

  per_try_idle_timeout_ = new Event::MockTimer(&callbacks_.dispatcher_);
  EXPECT_CALL(*per_try_idle_timeout_, enableTimer(std::chrono::milliseconds(3000), _));
  EXPECT_EQ(0U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());
  
  pool_callbacks->onPoolReady(encoder, cm_.thread_local_cluster_.conn_pool_.host_,
                              upstream_stream_info_, Http::Protocol::Http10);
  EXPECT_EQ(1U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());

  EXPECT_CALL(*per_try_idle_timeout_, enableTimer(std::chrono::milliseconds(3000), _));
  Http::ResponseHeaderMapPtr response_headers(
      new Http::TestResponseHeaderMapImpl{{"STR"}});
  response_decoder->decodeHeaders(std::move(response_headers), false);

  EXPECT_CALL(*per_try_idle_timeout_, enableTimer(std::chrono::milliseconds(3000), _));
  response_decoder->decodeData(data, false);

  EXPECT_CALL(*per_try_idle_timeout_, enableTimer(std::chrono::milliseconds(3000), _));
  EXPECT_CALL(*per_try_idle_timeout_, disableTimer());
  EXPECT_CALL(*response_timeout_, disableTimer());
  response_decoder->decodeData(data, true);
}