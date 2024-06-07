inline bool ResolveAxis(const int num_dims, const int* axis,
                        const int64_t num_axis, int* out_axis,
                        int* out_num_axis) {
  *out_num_axis = 0;  
  
  if (num_dims == 0) {
    return true;
  }
  
  for (int64_t idx = 0; idx < num_axis; ++idx) {
    
    
    
    int current = axis[idx] < 0 ? (axis[idx] + num_dims) : axis[idx];
    TFLITE_DCHECK(current >= 0 && current < num_dims);
    bool is_dup = false;
    for (int j = 0; j < *out_num_axis; ++j) {
      if (out_axis[j] == current) {
        is_dup = true;
        break;
      }
    }
    if (!is_dup) {
      out_axis[*out_num_axis] = current;
      *out_num_axis += 1;
    }
  }
  return true;
}