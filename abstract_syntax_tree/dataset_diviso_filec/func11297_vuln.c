  void Compute(OpKernelContext* ctx) override {
    auto value = ctx->input(0);
    auto update = ctx->input(1);

    OP_REQUIRES(
        ctx, value.dims() == update.dims(),
        errors::InvalidArgument("STR",
                                value.shape().DebugString(), "STR",
                                update.shape().DebugString()));
    for (int i = 1; i < value.dims(); ++i) {
      OP_REQUIRES(
          ctx, value.dim_size(i) == update.dim_size(i),
          errors::InvalidArgument("STR",
                                  value.shape().DebugString(), "STR",
                                  update.shape().DebugString()));
    }
    OP_REQUIRES(ctx, 1 == update.dim_size(0),
                errors::InvalidArgument("STR",
                                        update.shape().DebugString()));

    Tensor output = value;  
    const auto& d = ctx->eigen_device<Device>();
    OP_REQUIRES_OK(
        ctx, ::tensorflow::functor::DoParallelConcat(d, update, loc_, &output));
    ctx->set_output(0, output);
  }