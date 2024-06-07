TEST_F(NgramKernelTest, TestUnpaddedTrigramsAndBigramsWithPreserveShort) {
  MakeOp("STR", 0, true);
  
  
  
  AddInputFromArray<tstring>(TensorShape({6}), {"STR"});
  AddInputFromArray<int64>(TensorShape({3}), {0, 4, 6});
  TF_ASSERT_OK(RunOpKernel());

  
  
  std::vector<tstring> expected_values(
      {"STR"});
  std::vector<int64> expected_splits({0, 5, 6});

  assert_string_equal(expected_values, *GetOutput(0));
  assert_int64_equal(expected_splits, *GetOutput(1));
}