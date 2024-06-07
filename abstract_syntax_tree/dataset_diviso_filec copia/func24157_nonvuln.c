TEST_F(RouterTest, NoMetadataMatchCriteria) {
  ON_CALL(callbacks_.route_->route_entry_, metadataMatchCriteria()).WillByDefault(Return(nullptr));
  EXPECT_CALL(cm_.thread_local_cluster_, httpConnPool(_, _, _))
      .WillOnce(Invoke([&](Upstream::ResourcePriority, absl::optional<Http::Protocol>,
                           Upstream::LoadBalancerContext* context) {
        EXPECT_EQ(context->metadataMatchCriteria(), nullptr);
        return Upstream::HttpPoolData([]() {}, &cm_.thread_local_cluster_.conn_pool_);
      }));
  EXPECT_CALL(cm_.thread_local_cluster_.conn_pool_, newStream(_, _))
      .WillOnce(Return(&cancellable_));
  expectResponseTimerCreate();

  Http::TestRequestHeaderMapImpl headers;
  HttpTestUtility::addDefaultHeaders(headers);
  router_.decodeHeaders(headers, true);

  
  EXPECT_CALL(cancellable_, cancel(_));
  router_.onDestroy();
}