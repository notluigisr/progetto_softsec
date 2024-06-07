  explicit ReverseSequenceOp(OpKernelConstruction* context)
      : OpKernel(context) {
    OP_REQUIRES_OK(context, context->GetAttr("STR", &batch_dim_));
    OP_REQUIRES_OK(context, context->GetAttr("STR", &seq_dim_));
  }