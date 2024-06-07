  void Compute(OpKernelContext* ctx) override {
    const Tensor& indices = ctx->input(0);
    const auto values = ctx->input(1).flat<Tidx>();
    const Tensor& dense_shape = ctx->input(2);
    const Tensor& size_t = ctx->input(3);
    const auto weights = ctx->input(4).flat<T>();
    const int64_t weights_size = weights.size();

    Tidx size = size_t.scalar<Tidx>()();
    OP_REQUIRES(
        ctx, size >= 0,
        errors::InvalidArgument("STR"));

    bool is_1d = dense_shape.NumElements() == 1;

    Tensor* out_t;
    functor::SetZeroFunctor<Device, T> fill;
    if (is_1d) {
      OP_REQUIRES_OK(ctx, ctx->allocate_output(0, TensorShape({size}), &out_t));
      auto out = out_t->flat<T>();
      fill(ctx->eigen_device<Device>(), out);
      if (binary_output_) {
        OP_REQUIRES_OK(ctx,
                       functor::BincountFunctor<Device, Tidx, T, true>::Compute(
                           ctx, values, weights, out, size));
      } else {
        OP_REQUIRES_OK(
            ctx, functor::BincountFunctor<Device, Tidx, T, false>::Compute(
                     ctx, values, weights, out, size));
      }
    } else {
      const auto shape = dense_shape.flat<int64_t>();
      const int64_t num_rows = shape(0);
      OP_REQUIRES_OK(
          ctx, ctx->allocate_output(0, TensorShape({num_rows, size}), &out_t));
      const auto out = out_t->matrix<T>();
      fill(ctx->eigen_device<Device>(), out_t->flat<T>());
      const auto indices_mat = indices.matrix<int64_t>();
      for (int64_t i = 0; i < indices_mat.dimension(0); ++i) {
        const int64_t batch = indices_mat(i, 0);
        const Tidx bin = values(i);
        if (bin < size) {
          if (binary_output_) {
            out(batch, bin) = T(1);
          } else {
            if (weights_size) {
              out(batch, bin) += weights(i);
            } else {
              out(batch, bin) += T(1);
            }
          }
        }
      }
    }
  }