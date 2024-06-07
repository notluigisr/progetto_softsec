  void Compute(OpKernelContext* context) override {
    const Tensor& input = context->input(0);
    const Tensor& filter = context->input(1);

    
    int stride_rows = 0, stride_cols = 0;
    int rate_rows = 0, rate_cols = 0;
    int64 pad_top = 0, pad_left = 0;
    int64 out_rows = 0, out_cols = 0;
    ParseSizes(context, strides_, rates_, padding_, &stride_rows, &stride_cols,
               &rate_rows, &rate_cols, &pad_top, &pad_left, &out_rows,
               &out_cols);

    
    
    const int batch = input.dim_size(0);
    const int depth = input.dim_size(3);
    const std::vector<int64> out_sizes = {batch, out_rows, out_cols, depth};
    TensorShape out_shape(out_sizes);

    Tensor* output = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(0, out_shape, &output));

    
    if (out_shape.num_elements() == 0) {
      return;
    }

    functor::Dilation<Device, T>()(
        context->eigen_device<Device>(), input.tensor<T, 4>(),
        filter.tensor<T, 3>(), stride_rows, stride_cols, rate_rows, rate_cols,
        pad_top, pad_left, output->tensor<T, 4>());
  }