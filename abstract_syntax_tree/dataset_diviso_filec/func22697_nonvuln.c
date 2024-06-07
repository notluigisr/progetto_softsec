  explicit CTCLossOp(OpKernelConstruction* ctx) : OpKernel(ctx) {
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR",
                                     &preprocess_collapse_repeated_));
    OP_REQUIRES_OK(ctx,
                   ctx->GetAttr("STR", &ctc_merge_repeated_));
    OP_REQUIRES_OK(ctx, ctx->GetAttr("STR",
                                     &ignore_longer_outputs_than_inputs_));
  }