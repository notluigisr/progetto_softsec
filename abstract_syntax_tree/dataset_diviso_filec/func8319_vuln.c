  void Compute(OpKernelContext* context) override {
    const Tensor& tensor_in = context->input(0);
    const Tensor& tensor_out = context->input(1);
    const Tensor& out_grad_backprop = context->input(2);

    
    OP_REQUIRES(context, tensor_in.dims() == 5,
                errors::InvalidArgument("STR"));
    OP_REQUIRES(context, tensor_out.dims() == 5,
                errors::InvalidArgument("STR"));
    
    OP_REQUIRES(
        context, out_grad_backprop.dims() == 5,
        errors::InvalidArgument("STR"));

    Pool3dParameters params{context,  ksize_,       stride_,
                            padding_, data_format_, tensor_in.shape()};

    Tensor* output = nullptr;
    OP_REQUIRES_OK(context, context->forward_input_or_allocate_output(
                                {2}, 0, tensor_out.shape(), &output));

    
    
    OP_REQUIRES(context, tensor_in.NumElements() > 0,
                errors::InvalidArgument("STR",
                                        tensor_in.DebugString()));
    OP_REQUIRES(context, tensor_out.NumElements() > 0,
                errors::InvalidArgument("STR",
                                        tensor_out.DebugString()));
    OP_REQUIRES(
        context, out_grad_backprop.NumElements() > 0,
        errors::InvalidArgument("STR",
                                out_grad_backprop.DebugString()));

    LaunchMaxPooling3dGradGradOp<Device, T>::launch(
        context, params, tensor_in, tensor_out, out_grad_backprop, output);
  }