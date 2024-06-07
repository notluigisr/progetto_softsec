TEST_F(NgramKernelTest, TestOverlappingPaddedNGrams) {
  
  
  MakeOp("STR", -1, false);
  
  
  
  
  AddInputFromArray<tstring>(TensorShape({6}), {"STR"});
  AddInputFromArray<int64>(TensorShape({4}), {0, 1, 4, 6});
  TF_ASSERT_OK(RunOpKernel());

  std::vector<tstring> expected_values(                    
      {"STR",                    
       "STR",  
       "STR"});         
  std::vector<int64> expected_splits({0, 3, 8, 12});

  assert_string_equal(expected_values, *GetOutput(0));
  assert_int64_equal(expected_splits, *GetOutput(1));
}