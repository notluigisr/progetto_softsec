  static port::StatusOr<CudnnRnnSequenceTensorDescriptor> Create(
      GpuExecutor* parent, int max_seq_length, int batch_size, int data_size,
      cudnnDataType_t data_type) {
    CHECK_GT(max_seq_length, 0);
    int dims[] = {batch_size, data_size, 1};
    int strides[] = {dims[1] * dims[2], dims[2], 1};
    TensorDescriptor tensor_desc = CreateTensorDescriptor();
    RETURN_IF_CUDNN_ERROR(cudnnSetTensorNdDescriptor(
        tensor_desc.get(), data_type,
        sizeof(dims) / sizeof(dims[0]), dims,
        strides));
    return CudnnRnnSequenceTensorDescriptor(parent, max_seq_length, batch_size,
                                            data_size, data_type,
                                            nullptr,
                                            std::move(tensor_desc));
  }