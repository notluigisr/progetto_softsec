inline int ArgMaxVector(const T* input_data, int size) {
  T max_value = input_data[0];
  int max_index = 0;
  for (int i = 1; i < size; ++i) {
    const T curr_value = input_data[i];
    if (curr_value > max_value) {
      max_value = curr_value;
      max_index = i;
    }
  }
  return max_index;
}