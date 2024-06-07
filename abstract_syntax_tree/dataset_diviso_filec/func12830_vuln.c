  void Compute(OpKernelContext* ctx) override {
    
    ReshapeOp::Compute(ctx);

    const float input_min_float = ctx->input(2).flat<float>()(0);
    const float input_max_float = ctx->input(3).flat<float>()(0);
    Tensor* output_min = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(1, TensorShape({}), &output_min));
    output_min->flat<float>()(0) = input_min_float;

    Tensor* output_max = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(2, TensorShape({}), &output_max));
    output_max->flat<float>()(0) = input_max_float;
  }