  void Compute(OpKernelContext* context) override {
    const Tensor& data = context->input(0);
    const Tensor& segment_ids = context->input(1);
    const Tensor& num_segments = context->input(2);
    if (!UnsortedSegmentReductionDoValidation(this, context, data, segment_ids,
                                              num_segments)) {
      return;
    }
    const auto segment_flat = segment_ids.flat<Index>();
    const Index output_rows = internal::SubtleMustCopy(static_cast<Index>(
        num_segments.dtype() == DT_INT32 ? num_segments.scalar<int32>()()
                                         : num_segments.scalar<int64>()()));
    OP_REQUIRES(context, output_rows >= 0,
                errors::InvalidArgument("STR", output_rows,
                                        "STR"));
    TensorShape output_shape;
    output_shape.AddDim(output_rows);
    for (int i = segment_ids.dims(); i < data.dims(); i++) {
      output_shape.AddDim(data.dim_size(i));
    }
    Tensor* output = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(0, output_shape, &output));
    auto output_flat = output->flat_outer_dims<T>();
    auto data_ptr = data.template flat<T>().data();
    reduction_functor_(context, output_rows, segment_ids.shape(), segment_flat,
                       data.NumElements(), data_ptr, output_flat);
  }