TEST_F(AsStringGraphTest, Complex) {
  TF_ASSERT_OK(Init(DT_COMPLEX64, "", 5, 2));

  AddInputFromArray<complex64>(TensorShape({3}), {{-4, 2}, {0}, {3.14159, -1}});
  TF_ASSERT_OK(RunOpKernel());
  Tensor expected(allocator(), DT_STRING, TensorShape({3}));
  test::FillValues<tstring>(
      &expected, {"STR"});
  test::ExpectTensorEqual<tstring>(expected, *GetOutput(0));
}