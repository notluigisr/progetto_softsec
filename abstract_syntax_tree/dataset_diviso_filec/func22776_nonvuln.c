inline typename std::enable_if<is_int32_or_int64<T>::value, void>::type Add(
    const ArithmeticParams& params, const RuntimeShape& input1_shape,
    const T* input1_data, const RuntimeShape& input2_shape,
    const T* input2_data, const RuntimeShape& output_shape, T* output_data) {
  ruy::profiler::ScopeLabel label("STR");

  T activation_min, activation_max;
  GetActivationParams(params, &activation_min, &activation_max);

  auto input1_map = MapAsVector(input1_data, input1_shape);
  auto input2_map = MapAsVector(input2_data, input2_shape);
  auto output_map = MapAsVector(output_data, output_shape);
  if (input1_shape == input2_shape) {
    output_map.array() = (input1_map.array() + input2_map.array())
                             .cwiseMax(activation_min)
                             .cwiseMin(activation_max);
  } else if (input2_shape.FlatSize() == 1) {
    auto scalar = input2_data[0];
    output_map.array() = (input1_map.array() + scalar)
                             .cwiseMax(activation_min)
                             .cwiseMin(activation_max);
  } else if (input1_shape.FlatSize() == 1) {
    auto scalar = input1_data[0];
    output_map.array() = (scalar + input2_map.array())
                             .cwiseMax(activation_min)
                             .cwiseMin(activation_max);
  } else {
    reference_ops::BroadcastAdd4DSlow<T>(params, input1_shape, input1_data,
                                         input2_shape, input2_data,
                                         output_shape, output_data);
  }
}