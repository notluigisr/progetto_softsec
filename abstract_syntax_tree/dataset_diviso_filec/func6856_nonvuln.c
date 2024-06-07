TEST(GatherNdOpTest, Int64Int64) {
  GatherNdOpModel m({TensorType_INT64, {3, 2, 3}}, {TensorType_INT64, {2, 2}});
  m.SetInput<int64_t>({1LL, -1LL, 1LL, -2LL, 2LL, 2LL,   
                       3LL, 3LL, -3LL, -4LL, -4LL, 4LL,  
                       5LL, -5LL, 5LL, 6LL, -6LL, 6LL});
  m.SetPositions<int64_t>({0LL, 1LL, 1LL, 0LL});
  ASSERT_EQ(m.Invoke(), kTfLiteOk);

  EXPECT_THAT(m.GetOutput<int64_t>(),
              ElementsAreArray({-2LL, 2LL, 2LL, 3LL, 3LL, -3LL}));
}