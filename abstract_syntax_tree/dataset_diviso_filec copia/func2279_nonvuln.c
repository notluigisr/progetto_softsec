TYPED_TEST(MultiProtocolTest, FrozenStructA) {
  FrozenStructA oldObject = makeFrozenStructALike<FrozenStructA>();
  tablebased::FrozenStructA newObject =
      makeFrozenStructALike<tablebased::FrozenStructA>();
  EXPECT_COMPATIBLE_PROTOCOL(oldObject, newObject, TypeParam);
}