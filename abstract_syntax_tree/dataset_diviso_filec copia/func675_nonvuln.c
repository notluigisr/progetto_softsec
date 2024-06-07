  explicit FusedBatchNormGradOpBase(OpKernelConstruction* context)
      : OpKernel(context) {
    float epsilon;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &epsilon));
    epsilon_ = U(epsilon);
    string tensor_format;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &tensor_format));
    OP_REQUIRES(context, FormatFromString(tensor_format, &tensor_format_),
                errors::InvalidArgument("STR"));
    OP_REQUIRES_OK(context, context->GetAttr("STR", &is_training_));
  }