  void operator()(OpKernelContext* ctx, const Index num_segments,
                  const TensorShape& segment_ids_shape,
                  typename TTypes<Index>::ConstFlat segment_ids,
                  const Index data_size, const T* data,
                  typename TTypes<T, 2>::Tensor output) {
    output.setConstant(InitialValueF()());
    if (data_size == 0) {
      return;
    }
    const int64 N = segment_ids.dimension(0);
    ReductionF reduction;
    auto data_flat = typename TTypes<T, 2>::ConstTensor(data, N, data_size / N);
    for (int64 i = 0; i < N; ++i) {
      Index j = internal::SubtleMustCopy(segment_ids(i));
      if (j < 0) {
        continue;
      }
      OP_REQUIRES(ctx, FastBoundsCheck(j, num_segments),
                  errors::InvalidArgument(
                      "STR", SliceDebugString(segment_ids_shape, i),
                      "STR"));
      reduction(data_flat.template chip<0>(i), output.template chip<0>(j));
    }
  }