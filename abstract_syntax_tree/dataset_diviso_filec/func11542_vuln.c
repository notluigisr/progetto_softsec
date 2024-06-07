  void Compute(OpKernelContext* ctx) override {
    const Tensor& input = ctx->input(0);
    const int depth = (axis_ == -1) ? 1 : input.dim_size(axis_);
    Tensor* output = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, input.shape(), &output));

    Tensor num_bits_tensor;
    num_bits_tensor = ctx->input(3);
    int num_bits_val = num_bits_tensor.scalar<int32>()();

    OP_REQUIRES(
        ctx, num_bits_val > 0 && num_bits_val < (signed_input_ ? 62 : 63),
        errors::InvalidArgument("STR", num_bits_val,
                                "STR", signed_input_));

    Tensor input_min_tensor;
    Tensor input_max_tensor;
    if (range_given_) {
      input_min_tensor = ctx->input(1);
      input_max_tensor = ctx->input(2);
      if (axis_ == -1) {
        auto min_val = input_min_tensor.scalar<T>()();
        auto max_val = input_max_tensor.scalar<T>()();
        OP_REQUIRES(ctx, min_val <= max_val,
                    errors::InvalidArgument("STR",
                                            min_val, "STR", max_val));
      } else {
        OP_REQUIRES(ctx, input_min_tensor.dim_size(0) == depth,
                    errors::InvalidArgument(
                        "STR",
                        input_min_tensor.dim_size(0), "STR", depth,
                        "STR",
                        input_min_tensor.shape()));
        OP_REQUIRES(ctx, input_max_tensor.dim_size(0) == depth,
                    errors::InvalidArgument(
                        "STR",
                        input_max_tensor.dim_size(0), "STR", depth,
                        "STR",
                        input_max_tensor.shape()));
      }
    } else {
      auto range_shape = (axis_ == -1) ? TensorShape({}) : TensorShape({depth});
      OP_REQUIRES_OK(ctx, ctx->allocate_temp(DataTypeToEnum<T>::value,
                                             range_shape, &input_min_tensor));
      OP_REQUIRES_OK(ctx, ctx->allocate_temp(DataTypeToEnum<T>::value,
                                             range_shape, &input_max_tensor));
    }

    if (axis_ == -1) {
      functor::QuantizeAndDequantizeOneScaleFunctor<Device, T> f;
      f(ctx->eigen_device<Device>(), input.flat<T>(), signed_input_,
        num_bits_val, range_given_, &input_min_tensor, &input_max_tensor,
        ROUND_HALF_TO_EVEN, narrow_range_, output->flat<T>());
    } else {
      functor::QuantizeAndDequantizePerChannelFunctor<Device, T> f;
      f(ctx->eigen_device<Device>(),
        input.template flat_inner_outer_dims<T, 3>(axis_ - 1), signed_input_,
        num_bits_val, range_given_, &input_min_tensor, &input_max_tensor,
        ROUND_HALF_TO_EVEN, narrow_range_,
        output->template flat_inner_outer_dims<T, 3>(axis_ - 1));
    }
  }