TEST_F(RouterTest, PoolFailureWithPriority) {
  ON_CALL(callbacks_.route_->route_entry_, priority())
      .WillByDefault(Return(Upstream::ResourcePriority::High));
  EXPECT_CALL(cm_.thread_local_cluster_,
              httpConnPool(Upstream::ResourcePriority::High, _, &router_));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Invoke([&](Http::StreamDecoder&, Http::ConnectionPool::Callbacks& callbacks)
                           -> Http::ConnectionPool::Cancellable* {
        callbacks.onPoolFailure(ConnectionPool::PoolFailureReason::RemoteConnectionFailure,
                                "STR", cm_.thread_local_cluster_.conn_pool_.host_);
        return nullptr;
      }));

  Http::TestResponseHeaderMapImpl response_headers{
      {"STR"}};
  EXPECT_CALL(callbacks_, encodeHeaders_(HeaderMapEqualRef(&response_headers), false));
  EXPECT_CALL(callbacks_, encodeData(_, true));
  EXPECT_CALL(callbacks_.stream_info_,
              setResponseFlag(StreamInfo::ResponseFlag::UpstreamConnectionFailure));
  EXPECT_CALL(callbacks_.stream_info_, onUpstreamHostSelected(_))
      .WillOnce(Invoke([&](const Upstream::HostDescriptionConstSharedPtr host) -> void {
        EXPECT_EQ(host_address_, host->address());
      }));

  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, true);
  EXPECT_TRUE(verifyHostUpstreamStats(0, 1));
  
  EXPECT_EQ(0U,
            callbacks_.route_->route_entry_.virtual_cluster_.stats().upstream_rq_total_.value());
  EXPECT_EQ(callbacks_.details(),
            "STR");
}