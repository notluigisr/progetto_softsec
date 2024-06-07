inline void PadImageStyle(const tflite::PadParams& op_params,
                          const RuntimeShape& input_shape, const T* input_data,
                          const P* pad_value_ptr,
                          const RuntimeShape& output_shape, T* output_data) {
  reference_ops::PadImageStyle(op_params, input_shape, input_data,
                               pad_value_ptr, output_shape, output_data);
}