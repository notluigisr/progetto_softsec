  explicit QuantizedConv2DOp(OpKernelConstruction* context)
      : OpKernel(context) {
    OP_REQUIRES_OK(context, context->GetAttr("STR", &strides_));
    OP_REQUIRES(context, strides_.size() == 4,
                errors::InvalidArgument("STR"
                                        "STR"));
    OP_REQUIRES(context, strides_[1] == strides_[2],
                errors::InvalidArgument(
                    "STR"
                    "STR"));
    OP_REQUIRES(
        context, (strides_[0] == 1 && strides_[3] == 1),
        errors::InvalidArgument("STR"
                                "STR"));
    std::vector<int32> dilations;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &dilations));
    OP_REQUIRES(context, dilations.size() == 4,
                errors::InvalidArgument("STR"
                                        "STR"));
    OP_REQUIRES(context, dilations[1] == 1 && dilations[2] == 1,
                errors::InvalidArgument(
                    "STR"
                    "STR"));
    OP_REQUIRES(context, (dilations[0] == 1 && dilations[3] == 1),
                errors::InvalidArgument(
                    "STR"
                    "STR"));
    OP_REQUIRES_OK(context, context->GetAttr("STR", &padding_));
  }