  explicit DataFormatVecPermuteOp(OpKernelConstruction* context)
      : OpKernel(context) {
    string src_format;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &src_format));
    string dst_format;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &dst_format));
    src_format_ = src_format;
    dst_format_ = dst_format;
  }