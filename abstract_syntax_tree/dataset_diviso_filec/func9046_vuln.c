  void Compute(OpKernelContext* context) override {
    const Tensor& input = context->input(0);
    OP_REQUIRES(context, input.dims() == 1 || input.dims() == 2,
                errors::InvalidArgument(
                    "STR",
                    input.shape().DebugString()));
    if (input.dims() == 1) {
      OP_REQUIRES(context,
                  input.NumElements() == 2 || input.NumElements() == 4 ||
                      input.NumElements() == 5,
                  errors::InvalidArgument(
                      "STR",
                      input.shape().DebugString()));
    } else if (input.dims() == 2) {
      OP_REQUIRES(context, input.dim_size(0) == 2 || input.dim_size(0) == 4,
                  errors::InvalidArgument("STR"
                                          "STR",
                                          input.shape().DebugString()));
      OP_REQUIRES(
          context, input.dim_size(1) == 2,
          errors::InvalidArgument(
              "STR",
              input.shape().DebugString()));
    }

    Tensor* output = nullptr;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, input.shape(), &output));
    
    Eigen::DSizes<Eigen::DenseIndex, 8> dst_idx;
    string src_format_str = src_format_;
    string dst_format_str = dst_format_;
    if (input.dim_size(0) == 2) {
      
      
      auto keep_only_spatial_dimensions = [](string* format_str) -> void {
        auto new_end = std::remove_if(
            format_str->begin(), format_str->end(),
            [](const char dim) { return dim != 'H' && dim != 'W'; });
        format_str->erase(new_end, format_str->end());
      };
      keep_only_spatial_dimensions(&src_format_str);
      keep_only_spatial_dimensions(&dst_format_str);
    }
    ComputeDstIndex(src_format_str, dst_format_str, input.dims(), &dst_idx);

    functor::DataFormatVecPermute<Device, T>()(context->eigen_device<Device>(),
                                               input.flat<T>(),
                                               output->flat<T>(), dst_idx);
  }