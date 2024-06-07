TEST(GatherNdOpTest, SliceIndexingIntoMatrix) {
  GatherNdOpModel m({TensorType_FLOAT32, {2, 2}}, {TensorType_INT32, {2, 1}});
  m.SetInput<float>({1.1, 1.2, 2.1, 2.2});
  m.SetPositions<int32_t>({1, 0});
  ASSERT_EQ(m.Invoke(), kTfLiteOk);

  EXPECT_THAT(m.GetOutput<float>(), ElementsAreArray({2.1, 2.2, 1.1, 1.2}));
}