inline void Conv(const float* input_data, const Dims<4>& input_dims,
                 const float* filter_data, const Dims<4>& filter_dims,
                 const float* bias_data, const Dims<4>& bias_dims,
                 int stride_width, int stride_height, int dilation_width_factor,
                 int dilation_height_factor, int pad_width, int pad_height,
                 float output_activation_min, float output_activation_max,
                 float* output_data, const Dims<4>& output_dims,
                 float* im2col_data, const Dims<4>& im2col_dims) {
  tflite::ConvParams op_params;
  
  op_params.padding_type = PaddingType::kSame;
  op_params.padding_values.width = pad_width;
  op_params.padding_values.height = pad_height;
  op_params.stride_width = stride_width;
  op_params.stride_height = stride_height;
  op_params.dilation_width_factor = dilation_width_factor;
  op_params.dilation_height_factor = dilation_height_factor;
  op_params.float_activation_min = output_activation_min;
  op_params.float_activation_max = output_activation_max;

  Conv(op_params, DimsToShape(input_dims), input_data, DimsToShape(filter_dims),
       filter_data, DimsToShape(bias_dims), bias_data, DimsToShape(output_dims),
       output_data, DimsToShape(im2col_dims), im2col_data);
}