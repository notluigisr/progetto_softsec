  void operator()(OpKernelContext* ctx, bool use_cudnn, bool cudnn_use_autotune,
                  const Tensor& input, const Tensor& filter, int row_dilation,
                  int col_dilation, int row_stride, int col_stride,
                  const Padding& padding,
                  const std::vector<int64>& explicit_paddings, Tensor* output,
                  TensorFormat data_format) {
    if (data_format != FORMAT_NHWC) {
      ctx->SetStatus(errors::Unimplemented(
          "STR"
          "STR",
          ToString(data_format)));
      return;
    }

    for (int64 explicit_padding : explicit_paddings) {
      if (!FastBoundsCheck(explicit_padding, std::numeric_limits<int>::max())) {
        ctx->SetStatus(errors::InvalidArgument("STR"));
        return;
      }
    }

    const int64 in_depth = input.dim_size(3);
    const int64 out_depth = output->dim_size(3);
    const int64 patch_depth = filter.dim_size(2);

    if (in_depth % patch_depth != 0) {
      ctx->SetStatus(errors::InvalidArgument(
          "STR", in_depth,
          "STR", patch_depth));
      return;
    }

    const int64 num_groups = in_depth / patch_depth;
    if (out_depth % num_groups != 0 || out_depth < num_groups) {
      ctx->SetStatus(errors::InvalidArgument(
          "STR",
          out_depth, "STR", num_groups));
      return;
    }

    if (in_depth != patch_depth) {
      LaunchGrouped<T>()(ctx, input, filter, row_stride, col_stride,
                         row_dilation, col_dilation, padding, explicit_paddings,
                         output, data_format);
    } else {
      LaunchGeneric<CPUDevice, T>()(ctx, input, filter, row_stride, col_stride,
                                    row_dilation, col_dilation, padding,
                                    explicit_paddings, output, data_format);
    }
  }