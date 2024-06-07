inline void Pad(const T* input_data, const Dims<4>& input_dims,
                const std::vector<int>& left_paddings,
                const std::vector<int>& right_paddings, T* output_data,
                const Dims<4>& output_dims, const int32_t pad_value) {
  const T converted_pad_value = static_cast<T>(pad_value);
  PadV2<T>(input_data, input_dims, left_paddings, right_paddings, output_data,
           output_dims, converted_pad_value);
}