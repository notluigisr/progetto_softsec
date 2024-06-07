  void Compute(OpKernelContext* ctx) override {
    const Tensor& sorted_inputs_t = ctx->input(0);
    const Tensor& values_t = ctx->input(1);

    
    OP_REQUIRES(ctx, sorted_inputs_t.dim_size(0) == values_t.dim_size(0),
                Status(error::INVALID_ARGUMENT,
                       "STR"));

    
    OP_REQUIRES(ctx, values_t.NumElements() < std::numeric_limits<int>::max(),
                Status(error::INVALID_ARGUMENT,
                       "STR"));

    Tensor* output_t;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, values_t.shape(), &output_t));

    if (output_t->dtype() == DT_INT32) {
      OP_REQUIRES(ctx,
                  FastBoundsCheck(sorted_inputs_t.dim_size(1),
                                  std::numeric_limits<int>::max()),
                  errors::InvalidArgument("STR"
                                          "STR",
                                          sorted_inputs_t.dim_size(1)));
    }

    auto output = output_t->template flat<OutType>();
    const auto sorted_inputs = sorted_inputs_t.template flat<T>();
    const auto values = values_t.template flat<T>();
    OP_REQUIRES_OK(
        ctx, functor::LowerBoundFunctor<Device, T, OutType>::Compute(
                 ctx, sorted_inputs, values, sorted_inputs_t.dim_size(0),
                 sorted_inputs_t.dim_size(1), values_t.dim_size(1), &output));
  }