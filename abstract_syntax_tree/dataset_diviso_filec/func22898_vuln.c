  void Compute(OpKernelContext* context) override {
    const Tensor& input = context->input(0);
    const TensorShape& input_shape = input.shape();
    const int32_t input_dims = input_shape.dims();

    const Tensor& segment_id = context->input(1);
    const TensorShape& segment_id_shape = segment_id.shape();
    const int32_t segment_dims = segment_id_shape.dims();

    const Tensor& num_segments_tensor = context->input(2);
    OP_REQUIRES(context, num_segments_tensor.NumElements() != 0,
                errors::InvalidArgument("STR"));
    auto num_segments = num_segments_tensor.scalar<NUM_SEGMENTS_TYPE>()();

    OP_REQUIRES(
        context, num_segments >= 0,
        errors::InvalidArgument(
            "STR", num_segments));
    OP_REQUIRES(context, segment_dims != 0,
                errors::InvalidArgument("STR"));

    OP_REQUIRES(
        context, segment_dims <= input_dims,
        errors::OutOfRange("STR", segment_dims,
                           "STR"));
    for (auto i = 0; i < segment_dims; i++) {
      OP_REQUIRES(
          context, segment_id_shape.dim_size(i) == input_shape.dim_size(i),
          errors::InvalidArgument(
              "STR", segment_id_shape.dim_size(i),
              "STR", i));
    }

    
    Tensor* output_tensor = nullptr;
    TensorShape output_shape =
        GetOutputShape(input_shape, segment_id_shape, num_segments);
    OP_REQUIRES_OK(context, context->allocate_output("STR", output_shape,
                                                     &output_tensor));

    
    auto output_flat = output_tensor->flat<tstring>();
    auto flat_segment_id = segment_id.flat<INDICES_TYPE>();
    auto flat_input = input.flat<tstring>();

    for (int i = 0; i < flat_segment_id.size(); i++) {
      OP_REQUIRES(
          context,
          ((flat_segment_id(i) < num_segments) && (flat_segment_id(i) >= 0)),
          errors::InvalidArgument(
              "STR"
              "STR"));
    }

    int64_t big_stride;
    int64_t small_stride;
    std::tie(big_stride, small_stride) =
        GetStrides<INDICES_TYPE>(input_shape, segment_id_shape);
    auto relative_offset_set =
        GetFlattenedRelativeOffsets<INDICES_TYPE>(small_stride, big_stride);
    for (auto start_offset = 0; start_offset < big_stride; start_offset++) {
      for (auto i = 0; i < relative_offset_set.size(); i++) {
        auto output_index = start_offset + flat_segment_id(i) * big_stride;
        auto offset = start_offset + relative_offset_set[i];
        if (output_flat(output_index).length() != 0)
          output_flat(output_index).append(separator_.c_str());
        output_flat(output_index).append(flat_input(offset));
      }
    }
  }