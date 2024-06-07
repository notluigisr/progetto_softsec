  void operator()(OpKernelContext* ctx, const Index num_segments,
                  const TensorShape& segment_ids_shape,
                  typename TTypes<Index>::ConstFlat segment_ids,
                  const Index data_size, const T* data,
                  typename TTypes<T, 2>::Tensor output) {
    if (output.size() == 0) {
      return;
    }
    
    GPUDevice d = ctx->template eigen_device<GPUDevice>();
    GpuLaunchConfig config = GetGpuLaunchConfig(output.size(), d);
    TF_CHECK_OK(GpuLaunchKernel(
        SetToValue<T>, config.block_count, config.thread_per_block, 0,
        d.stream(), output.size(), output.data(), InitialValueF()()));
    if (data_size == 0 || segment_ids_shape.num_elements() == 0) {
      return;
    }
    
    
    
    
    
    const Index input_outer_dim_size = segment_ids.dimension(0);
    const Index input_inner_dim_size = data_size / input_outer_dim_size;
    config = GetGpuLaunchConfig(data_size, d);

    TF_CHECK_OK(
        GpuLaunchKernel(UnsortedSegmentCustomKernel<T, Index, ReductionF>,
                        config.block_count, config.thread_per_block, 0,
                        d.stream(), input_outer_dim_size, input_inner_dim_size,
                        num_segments, segment_ids.data(), data, output.data()));
  }