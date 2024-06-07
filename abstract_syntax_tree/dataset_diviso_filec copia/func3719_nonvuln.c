  void operator()(cudnnRNNDescriptor_t descriptor) const {
    CHECK_CUDNN_OK(cudnnDestroyRNNDescriptor(descriptor));
  }