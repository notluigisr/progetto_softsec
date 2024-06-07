  explicit AsStringOp(OpKernelConstruction* ctx) : OpKernel(ctx) {
    int32 precision;
    bool scientific;
    bool shortest;
    int32 width;
    string fill_string;
    DataType dtype;
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &dtype));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &precision));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &scientific));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &shortest));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &width));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR", &fill_string));
    switch (dtype) {
      case DT_FLOAT:
      case DT_DOUBLE:
      case DT_COMPLEX64:
      case DT_COMPLEX128:
        break;
      default:
        OP_REQUIRES(ctx, !(scientific || shortest),
                    errors::InvalidArgument("STR"
                                            "STR",
                                            DataTypeString(dtype)));
        OP_REQUIRES(ctx, precision < 0,
                    errors::InvalidArgument("STR"
                                            "STR",
                                            DataTypeString(dtype)));
    }
    OP_REQUIRES(
        ctx, fill_string.size() <= 1,
        errors::InvalidArgument("STR"));
    OP_REQUIRES(ctx, !(scientific && shortest),
                errors::InvalidArgument(
                    "STR"));
    format_ = "STR";
    if (width > -1) {
      strings::Appendf(&format_, "STR", fill_string.c_str(), width);
    }
    if (precision > -1) {
      strings::Appendf(&format_, "STR", precision);
    }
    switch (dtype) {
      case DT_INT8:
      case DT_INT16:
      case DT_INT32:
        strings::Appendf(&format_, "STR");
        break;
      case DT_INT64:
        strings::Appendf(&format_, "STR");
        break;
      case DT_FLOAT:
      case DT_DOUBLE:
      case DT_COMPLEX64:
      case DT_COMPLEX128:
        if (shortest) {
          strings::Appendf(&format_, "STR");
        } else if (scientific) {
          strings::Appendf(&format_, "STR");
        } else {
          strings::Appendf(&format_, "STR");
        }
        break;
      case DT_BOOL:
        break;
      default:
        bool type_not_supported = true;
        OP_REQUIRES(ctx, !type_not_supported,
                    errors::InvalidArgument("STR",
                                            DataTypeString(dtype)));
    }

    if (dtype == DT_COMPLEX64 || dtype == DT_COMPLEX128) {
      format_ = strings::Printf("STR", format_.c_str(), format_.c_str());
    }
  }