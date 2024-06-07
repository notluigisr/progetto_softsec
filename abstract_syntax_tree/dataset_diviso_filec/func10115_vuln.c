  static port::StatusOr<CudnnRnnSequenceTensorDescriptor> Create(
      GpuExecutor* parent, int max_seq_length, int batch_size, int data_size,
      const absl::Span<const int>& seq_lengths, bool time_major,
      cudnnDataType_t data_type) {
    CHECK_GT(max_seq_length, 0);
    int dims[] = {batch_size, data_size, 1};
    int strides[] = {dims[1] * dims[2], dims[2], 1};
    TensorDescriptor tensor_desc = CreateTensorDescriptor();
    RETURN_IF_CUDNN_ERROR(cudnnSetTensorNdDescriptor(
        tensor_desc.get(), data_type,
        sizeof(dims) / sizeof(dims[0]), dims,
        strides));
    const int* seq_lengths_array = seq_lengths.data();
    RNNDataDescriptor data_desc = CreateRNNDataDescriptor();
    float padding_fill = 0.0f;
    cudnnRNNDataLayout_t layout;
    if (time_major) {
      layout = CUDNN_RNN_DATA_LAYOUT_SEQ_MAJOR_UNPACKED;
    } else {
      layout = CUDNN_RNN_DATA_LAYOUT_BATCH_MAJOR_UNPACKED;
    }
    RETURN_IF_CUDNN_ERROR(cudnnSetRNNDataDescriptor(
        data_desc.get(),  data_type,
        layout,
        max_seq_length,
        batch_size, data_size,
        seq_lengths_array,
         (void*)&padding_fill));
    return CudnnRnnSequenceTensorDescriptor(
        parent, max_seq_length, batch_size, data_size, data_type,
        std::move(data_desc), std::move(tensor_desc));
  }