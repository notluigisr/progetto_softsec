  void Compute(OpKernelContext* context) override {
    
    
    
    
    const Tensor* epsilon_t;
    OP_REQUIRES_OK(context, context->input(kEpsilonName, &epsilon_t));
    float epsilon = epsilon_t->scalar<float>()();
    OP_REQUIRES(
        context, epsilon > 0,
        errors::InvalidArgument("STR"));

    const Tensor* num_streams_t;
    OP_REQUIRES_OK(context, context->input(kNumStreamsName, &num_streams_t));
    int64_t num_streams = num_streams_t->scalar<int64>()();

    auto result =
        new QuantileStreamResource(epsilon, max_elements_, num_streams);
    auto status = CreateResource(context, HandleFromInput(context, 0), result);
    if (!status.ok() && status.code() != tensorflow::error::ALREADY_EXISTS) {
      OP_REQUIRES(context, false, status);
    }
  }