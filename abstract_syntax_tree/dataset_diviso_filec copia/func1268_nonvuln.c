inline void ResizeBilinear(const float* input_data, const Dims<4>& input_dims,
                           const int32* output_size_data,
                           const Dims<4>& output_size_dims, float* output_data,
                           const Dims<4>& output_dims, bool align_corners) {
  tflite::ResizeBilinearParams op_params;
  op_params.align_corners = align_corners;
  op_params.half_pixel_centers = false;
  ResizeBilinear(op_params, DimsToShape(input_dims), input_data,
                 DimsToShape(output_size_dims), output_size_data,
                 DimsToShape(output_dims), output_data);
}