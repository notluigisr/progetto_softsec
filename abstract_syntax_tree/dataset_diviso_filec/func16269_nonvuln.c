TEST_F(RouterTest, HashKeyNoHashPolicy) {
  ON_CALL(callbacks_.route_->route_entry_, hashPolicy()).WillByDefault(Return(nullptr));
  EXPECT_FALSE(router_.computeHashKey().has_value());
}