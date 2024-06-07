inline void Logistic(const float* input_data, const Dims<4>& input_dims,
                     float* output_data, const Dims<4>& output_dims) {
  Logistic(DimsToShape(input_dims), input_data, DimsToShape(output_dims),
           output_data);
}