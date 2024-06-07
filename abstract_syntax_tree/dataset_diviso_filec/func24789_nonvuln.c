inline int ArgMaxVector(const uint8_t* input_data, int size) {
  int32_t max_index = 0;
  uint8_t max_value = input_data[0];
  int32_t i = 0;
#ifdef USE_NEON
  constexpr int VECTOR_SIZE = 16;
  if (size >= VECTOR_SIZE) {
    uint8x16_t max_value_u8x16;
    for (; i <= size - VECTOR_SIZE; i += VECTOR_SIZE) {
      max_value_u8x16 = vld1q_u8(input_data + i);
      uint8_t max_from_vec;
#ifdef __aarch64__
      max_from_vec = vmaxvq_u8(max_value_u8x16);
#else   
      uint8x8_t max_val_u8x8 =
          vpmax_u8(vget_low_u8(max_value_u8x16), vget_high_u8(max_value_u8x16));
      max_val_u8x8 = vpmax_u8(max_val_u8x8, max_val_u8x8);
      max_val_u8x8 = vpmax_u8(max_val_u8x8, max_val_u8x8);
      max_val_u8x8 = vpmax_u8(max_val_u8x8, max_val_u8x8);
      max_from_vec = vget_lane_u8(max_val_u8x8, 0);
#endif  
      if (max_from_vec > max_value) {
        max_value = max_from_vec;
        max_index = i;
      }
    }
  }
  for (int start_idx = max_index; start_idx < max_index + VECTOR_SIZE;
       start_idx++) {
    if (input_data[start_idx] == max_value) {
      max_index = start_idx;
      break;
    }
  }

#endif  
  
  for (; i < size; ++i) {
    const uint8_t curr_value = input_data[i];
    if (curr_value > max_value) {
      max_value = curr_value;
      max_index = i;
    }
  }

  return max_index;
}