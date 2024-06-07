Status GetWindowedOutputSizeFromDims(
    shape_inference::InferenceContext* c,
    shape_inference::DimensionHandle input_size,
    shape_inference::DimensionOrConstant filter_size, int64_t stride,
    Padding padding_type, shape_inference::DimensionHandle* output_size) {
  if (padding_type == Padding::EXPLICIT) {
    return errors::Internal(
        "STR"
        "STR");
  }
  return GetWindowedOutputSizeFromDimsV2(c, input_size, filter_size,
                                         1, stride,
                                         padding_type,
                                         
                                         
                                         
                                         -1, -1, output_size);
}