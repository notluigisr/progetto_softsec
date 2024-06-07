  explicit DecodeBmpOp(OpKernelConstruction* context) : OpKernel(context) {
    OP_REQUIRES_OK(context, context->GetAttr("STR", &channels_));
    OP_REQUIRES(
        context,
        channels_ == 0 || channels_ == 1 || channels_ == 3 || channels_ == 4,
        errors::InvalidArgument("STR",
                                channels_));
  }