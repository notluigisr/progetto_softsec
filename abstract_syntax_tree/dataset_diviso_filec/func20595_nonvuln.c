port::Status CheckRNNParameterSize(
    const CudnnHandle& cudnn, const CudnnRnnDescriptor& rnn_desc,
    const CudnnRnnSequenceTensorDescriptor& input_desc) {
  size_t params_size_in_bytes = 0;
  RETURN_IF_CUDNN_ERROR(cudnnGetRNNParamsSize(
      cudnn.handle(), rnn_desc.handle(),
      input_desc.handles()[0], &params_size_in_bytes,
      rnn_desc.data_type()));
  if (static_cast<int64>(params_size_in_bytes) !=
      rnn_desc.ParamsSizeInBytes()) {
    return port::Status(port::error::INVALID_ARGUMENT,
                        "STR");
  }
  return port::Status::OK();
}