void Conv(const uint8* input_data, const Dims<4>& input_dims,
          int32 input_offset, const uint8* filter_data,
          const Dims<4>& filter_dims, int32 filter_offset,
          const int32* bias_data, const Dims<4>& bias_dims, int stride,
          int pad_width, int pad_height, int32 output_offset,
          int32 output_multiplier, int output_shift,
          int32 output_activation_min, int32 output_activation_max,
          uint8* output_data, const Dims<4>& output_dims, uint8* im2col_data,
          const Dims<4>& im2col_dims, gemmlowp::GemmContext* gemmlowp_context) {
  Conv<Ac>(input_data, input_dims, input_offset, filter_data, filter_dims,
           filter_offset, bias_data, bias_dims, stride, stride, pad_width,
           pad_height, output_offset, output_multiplier, output_shift,
           output_activation_min, output_activation_max, output_data,
           output_dims, im2col_data, im2col_dims, gemmlowp_context);
}