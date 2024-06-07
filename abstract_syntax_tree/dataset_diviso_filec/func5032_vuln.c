  void Compute(OpKernelContext* ctx) override {
    const Tensor& values_tensor = ctx->input(0);
    const Tensor& value_range_tensor = ctx->input(1);
    const Tensor& nbins_tensor = ctx->input(2);

    OP_REQUIRES(ctx, TensorShapeUtils::IsVector(value_range_tensor.shape()),
                errors::InvalidArgument("STR"));
    OP_REQUIRES(ctx, (value_range_tensor.shape().num_elements() == 2),
                errors::InvalidArgument(
                    "STR"));
    OP_REQUIRES(ctx, TensorShapeUtils::IsScalar(nbins_tensor.shape()),
                errors::InvalidArgument("STR"));

    const auto values = values_tensor.flat<T>();
    const auto value_range = value_range_tensor.flat<T>();
    const auto nbins = nbins_tensor.scalar<int32>()();

    OP_REQUIRES(
        ctx, (value_range(0) < value_range(1)),
        errors::InvalidArgument("STR"
                                "STR",
                                value_range(0), "STR"));
    OP_REQUIRES(
        ctx, (nbins > 0),
        errors::InvalidArgument("STR",
                                nbins, "STR"));

    Tensor* out_tensor;
    OP_REQUIRES_OK(ctx,
                   ctx->allocate_output(0, TensorShape({nbins}), &out_tensor));
    auto out = out_tensor->flat<Tout>();

    OP_REQUIRES_OK(
        ctx, functor::HistogramFixedWidthFunctor<Device, T, Tout>::Compute(
                 ctx, values, value_range, nbins, out));
  }