TF_LITE_MICRO_TEST(GatherNd_BatchedIndexingIntoRank3Tensor1) {
  
  
  int input_dims[] = {3, 3, 2, 3};
  int index_dims[] = {3, 2, 1, 3};
  const int32_t index_data[] = {0, 0, 1, 1, 1, 0};
  const float input_data[] = {1.1, -1.2, 1.3,  -2.1, 2.2,  2.3,  
                              3.1, 3.2,  -3.3, -4.1, -4.2, 4.3,  
                              5.1, -5.2, 5.3,  6.1,  -6.2, 6.3};
  const float golden_data[] = {-1.2, -4.1};
  float output_data[2];
  int output_dims[] = {2, 0, 0};
  tflite::testing::TestGatherNd<float, int32_t>(
      input_dims, input_data, index_dims, index_data, output_dims, output_data,
      golden_data);
}