TEST(QuantizedUInt8PoolingOpTest, MaxPoolPaddingValidStride1) {
  
  
  
  QuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, 0, 15.9375}, Padding_VALID, 1, 1);
  m.SetInput({
      0, 6, 2, 4,   
      3, 2, 10, 7,  
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({6, 10, 10})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({96, 160, 160}));
}