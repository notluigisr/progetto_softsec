  void Compute(OpKernelContext* context) override {
    const Tensor& image = context->input(0);
    OP_REQUIRES(context, image.dims() == 3,
                errors::InvalidArgument("STR",
                                        image.shape().DebugString()));
    OP_REQUIRES(
        context,
        FastBoundsCheck(image.NumElements(), std::numeric_limits<int32>::max()),
        errors::InvalidArgument("STR"));
    const int32 height = static_cast<int32>(image.dim_size(0));
    const int32 width = static_cast<int32>(image.dim_size(1));
    const int32 channels = static_cast<int32>(image.dim_size(2));

    
    const int32 max_row_width = std::numeric_limits<int32>::max() / 2;

    OP_REQUIRES(context, FastBoundsCheck(width * channels, max_row_width),
                errors::InvalidArgument("STR"));

    OP_REQUIRES(context, channels >= 1 && channels <= 4,
                errors::InvalidArgument(
                    "STR", channels));

    
    Tensor* output = nullptr;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, TensorShape({}), &output));
    if (desired_channel_bits_ == 8) {
      OP_REQUIRES(context,
                  png::WriteImageToBuffer(
                      image.flat<uint8>().data(), width, height,
                      width * channels, channels, desired_channel_bits_,
                      compression_, &output->scalar<tstring>()(), nullptr),
                  errors::Internal("STR"));
    } else {
      OP_REQUIRES(context,
                  png::WriteImageToBuffer(
                      image.flat<uint16>().data(), width, height,
                      width * channels * 2, channels, desired_channel_bits_,
                      compression_, &output->scalar<tstring>()(), nullptr),
                  errors::Internal("STR"));
    }
  }