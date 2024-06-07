port::Status CudnnSupport::DoCtcLoss(
    Stream* stream, dnn::DataType element_type,
    const dnn::RnnStateTensorDescriptor& probs_desc,
    const DeviceMemoryBase probs_data, absl::Span<const int> labels_data,
    absl::Span<const int> labels_lengths_data,
    absl::Span<const int> input_lengths_data, DeviceMemoryBase costs_data,
    const dnn::RnnStateTensorDescriptor& grads_desc,
    DeviceMemoryBase grads_data, DeviceMemory<uint8> scratch_memory,
    int ctc_loss_algo_id) {
  
  if (CUDNN_VERSION < 7603 || element_type != dnn::DataType::kFloat) {
    return port::Status(port::error::INVALID_ARGUMENT,
                        "STR"
                        "STR");
  }
  CudnnCtcLossDescriptor cudnn_ctc_loss_desc(ToCudnnDataType(element_type));
  const CudnnRnnStateTensorDescriptor& cudnn_probs_desc =
      static_cast<const CudnnRnnStateTensorDescriptor&>(probs_desc);
  const CudnnRnnStateTensorDescriptor& cudnn_grads_desc =
      static_cast<const CudnnRnnStateTensorDescriptor&>(grads_desc);
  return DoCtcLossImpl(stream, cudnn_probs_desc, probs_data, labels_data,
                       labels_lengths_data, input_lengths_data, costs_data,
                       cudnn_grads_desc, grads_data, cudnn_ctc_loss_desc,
                       scratch_memory, ctc_loss_algo_id);
}