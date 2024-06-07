  explicit DataFormatDimMapOp(OpKernelConstruction* context)
      : OpKernel(context) {
    string src_format;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &src_format));
    string dst_format;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &dst_format));
    OP_REQUIRES(context, src_format.size() == 4 || src_format.size() == 5,
                errors::InvalidArgument(strings::StrCat(
                    "STR"
                    "STR",
                    src_format)));
    OP_REQUIRES(
        context, dst_format.size() == 4 || dst_format.size() == 5,
        errors::InvalidArgument(strings::StrCat(
            "STR",
            dst_format)));
    dst_idx_ = Tensor(DT_INT32, {static_cast<int64>(src_format.size())});
    for (int i = 0; i < src_format.size(); ++i) {
      for (int j = 0; j < dst_format.size(); ++j) {
        if (dst_format[j] == src_format[i]) {
          dst_idx_.vec<int>()(i) = j;
          break;
        }
      }
    }
  }