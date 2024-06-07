  void ValidateInputTensors(OpKernelContext* ctx, const Tensor& in0,
                            const Tensor& in1) override {
    const auto in0_num_dims = in0.dims();
    OP_REQUIRES(
        ctx, in0_num_dims >= 2,
        errors::InvalidArgument("STR", in0_num_dims));

    const auto in1_num_dims = in1.dims();
    OP_REQUIRES(
        ctx, in1_num_dims >= 2,
        errors::InvalidArgument("STR", in1_num_dims));

    const auto in0_last_dim = in0.dim_size(in0_num_dims - 1);
    const auto in0_prev_dim = in0.dim_size(in0_num_dims - 2);
    OP_REQUIRES(ctx, in0_last_dim == in0_prev_dim,
                errors::InvalidArgument(
                    "STR",
                    in0_last_dim, "STR"));
  }