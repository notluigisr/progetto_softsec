  void Compute(OpKernelContext* context) override {
    const Tensor& input = context->input(0);
    const Tensor& filter = context->input(1);
    const Tensor& out_backprop = context->input(2);

    
    int stride_rows = 0, stride_cols = 0;
    int rate_rows = 0, rate_cols = 0;
    int64 pad_top = 0, pad_left = 0;
    int64 out_rows = 0, out_cols = 0;
    ParseSizes(context, strides_, rates_, padding_, &stride_rows, &stride_cols,
               &rate_rows, &rate_cols, &pad_top, &pad_left, &out_rows,
               &out_cols);

    
    
    const int batch = input.dim_size(0);
    const int depth = input.dim_size(3);
    OP_REQUIRES(context,
                batch == out_backprop.dim_size(0) &&
                    out_rows == out_backprop.dim_size(1) &&
                    out_cols == out_backprop.dim_size(2) &&
                    depth == out_backprop.dim_size(3),
                errors::InvalidArgument("STR"));

    
    
    Tensor* in_backprop = nullptr;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, input.shape(), &in_backprop));

    
    if (input.shape().num_elements() == 0) {
      return;
    }

    functor::DilationBackpropInput<Device, T>()(
        context->eigen_device<Device>(), input.tensor<T, 4>(),
        filter.tensor<T, 3>(), out_backprop.tensor<T, 4>(), stride_rows,
        stride_cols, rate_rows, rate_cols, pad_top, pad_left,
        in_backprop->tensor<T, 4>());
  }