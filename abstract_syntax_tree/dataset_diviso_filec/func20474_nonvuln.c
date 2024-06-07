TEST(GatherNdOpTest, Uint8Int64) {
  GatherNdOpModel m({TensorType_UINT8, {3, 2, 3}}, {TensorType_INT64, {2, 2}});
  m.SetInput<uint8_t>({1, 1, 1, 2, 2, 2,  
                       3, 3, 3, 4, 4, 4,  
                       5, 5, 5, 6, 6, 6});
  m.SetPositions<int64_t>({0, 1, 1, 0});
  ASSERT_EQ(m.Invoke(), kTfLiteOk);

  EXPECT_THAT(m.GetOutput<uint8_t>(), ElementsAreArray({2, 2, 2, 3, 3, 3}));
}