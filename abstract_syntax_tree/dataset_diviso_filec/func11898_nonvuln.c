FilterDescriptor CreateFilterDescriptor() {
  cudnnFilterDescriptor_t result;
  CHECK_CUDNN_OK(cudnnCreateFilterDescriptor(&result));
  return FilterDescriptor(result);
}