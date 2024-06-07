bool CanFuseConvOrDepthwiseConvShapes(const ArrayRef<int64_t> filter_shape,
                                      const ArrayRef<int64_t> elements_shape,
                                      bool is_depthwise) {
  
  
  
  const auto elements_rank = elements_shape.size();
  for (int i = 0; i < static_cast<int>(elements_shape.size()) - 1; ++i) {
    if (elements_shape[i] != 1) return false;
  }
  if (elements_rank != 1 && elements_rank != 0 && elements_rank != 4) {
    return false;
  }
  auto elements_depth = elements_shape.empty() ? 1 : elements_shape.back();
  
  
  if (elements_depth == 1) {
    return true;
  }

  
  
  
  
  
  if (filter_shape.empty() ||
      (is_depthwise ? filter_shape.back() != elements_depth
                    : filter_shape[0] != elements_depth))
    return false;
  return true;
}