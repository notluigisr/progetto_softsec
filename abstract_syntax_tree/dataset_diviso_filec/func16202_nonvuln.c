inline void Mul(const int16* input1_data, const Dims<4>& input1_dims,
                const int16* input2_data, const Dims<4>& input2_dims,
                int32 output_offset, int32 output_activation_min,
                int32 output_activation_max, uint8* output_data,
                const Dims<4>& output_dims) {
  tflite::ArithmeticParams op_params;
  op_params.output_offset = output_offset;
  op_params.quantized_activation_min = output_activation_min;
  op_params.quantized_activation_max = output_activation_max;

  Mul(op_params, DimsToShape(input1_dims), input1_data,
      DimsToShape(input2_dims), input2_data, DimsToShape(output_dims),
      output_data);
}