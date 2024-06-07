  void Compute(OpKernelContext* ctx) override {
    const Tensor& input = ctx->input(0);
    const float input_min_float = ctx->input(1).flat<float>()(0);
    const float input_max_float = ctx->input(2).flat<float>()(0);
    Tensor* output_min = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, TensorShape({}), &output_min));
    Tensor* output_max = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(1, TensorShape({}), &output_max));

    qint32 used_min_quantized;
    qint32 used_max_quantized;
    CalculateUsedRange(input, &used_min_quantized, &used_max_quantized);

    
    
    const float used_min_float = std::min(
        0.0f,
        QuantizedToFloat(used_min_quantized, input_min_float, input_max_float));
    const float used_max_float =
        QuantizedToFloat(used_max_quantized, input_min_float, input_max_float);

    output_min->flat<float>().setConstant(used_min_float);
    output_max->flat<float>().setConstant(used_max_float);
  }