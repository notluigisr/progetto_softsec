AllocateCudnnConvolutionBackwardDataWorkspace(
    Stream* stream, const CudnnHandle& cudnn,
    const CudnnTensorDescriptor& input_nd, const CudnnFilterDescriptor& filter,
    const CudnnConvolutionDescriptor& conv,
    const CudnnTensorDescriptor& output_nd,
    const dnn::AlgorithmDesc& algorithm_desc,
    ScratchAllocator* scratch_allocator) {
  if (IsTensorMathOpSet(conv) != algorithm_desc.tensor_ops_enabled()) {
    return port::Status(
        port::error::INTERNAL,
        "STR");
  }

  
  size_t size_in_bytes;
  RETURN_IF_CUDNN_ERROR(cudnnGetConvolutionBackwardDataWorkspaceSize(
      cudnn.handle(),
      filter.handle(),
      output_nd.handle(),
      conv.handle(),
      input_nd.handle(),
      ToConvBackwardDataAlgo(algorithm_desc),
      &size_in_bytes));

  int64 size_in_bytes_int64 = size_in_bytes;

  if (TF_PREDICT_FALSE(size_in_bytes_int64 < 0)) {
    return port::Status(
        port::error::INTERNAL,
        "STR"
        "STR");
  }

  if (size_in_bytes_int64 == 0) {
    return DeviceMemory<uint8>();
  }

  if (TF_PREDICT_FALSE(!scratch_allocator)) {
    return port::Status(port::error::INVALID_ARGUMENT,
                        "STR");
  }

  return scratch_allocator->AllocateBytes(size_in_bytes);
}