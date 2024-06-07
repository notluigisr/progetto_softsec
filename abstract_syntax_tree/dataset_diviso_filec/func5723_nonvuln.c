  void Compute(OpKernelContext* ctx) override {
    const Tensor& shape_tensor = ctx->input(0);
    const Tensor& seed_tensor = ctx->input(1);
    const Tensor& means_tensor = ctx->input(2);
    const Tensor& stddevs_tensor = ctx->input(3);
    const Tensor& minvals_tensor = ctx->input(4);
    const Tensor& maxvals_tensor = ctx->input(5);

    OP_REQUIRES(ctx, seed_tensor.dims() == 1 && seed_tensor.dim_size(0) == 2,
                errors::InvalidArgument("STR",
                                        seed_tensor.shape().DebugString()));

    tensorflow::BCastList<4> bcast(
        {means_tensor.shape().dim_sizes(), stddevs_tensor.shape().dim_sizes(),
         minvals_tensor.shape().dim_sizes(),
         maxvals_tensor.shape().dim_sizes()},
        false,
        true);

    OP_REQUIRES(ctx, bcast.IsValid(),
                errors::InvalidArgument(
                    "STR"
                    "STR",
                    means_tensor.shape().DebugString(), "STR",
                    stddevs_tensor.shape().DebugString(), "STR",
                    minvals_tensor.shape().DebugString(), "STR",
                    maxvals_tensor.shape().DebugString()));

    
    TensorShape bcast_shape = BCast::ToShape(bcast.output_shape());
    OP_REQUIRES(
        ctx, TensorShapeUtils::IsVector(shape_tensor.shape()),
        errors::InvalidArgument("STR",
                                shape_tensor.shape().DebugString()));
    TensorShape output_shape;
    if (shape_tensor.dtype() == DataType::DT_INT32) {
      OP_REQUIRES_OK(ctx, TensorShapeUtils::MakeShape(shape_tensor.vec<int32>(),
                                                      &output_shape));
    } else {
      OP_REQUIRES_OK(ctx, TensorShapeUtils::MakeShape(shape_tensor.vec<int64>(),
                                                      &output_shape));
    }
    OP_REQUIRES(ctx, TensorShapeUtils::EndsWith(output_shape, bcast_shape),
                errors::InvalidArgument(
                    "STR"));

    int64 samples_per_batch = 1;
    const int64 num_sample_dims =
        (shape_tensor.dim_size(0) - bcast.output_shape().size());
    for (int64 i = 0; i < num_sample_dims; ++i) {
      samples_per_batch *= output_shape.dim_size(i);
    }
    int64 num_batches = 1;
    for (int64 i = num_sample_dims; i < shape_tensor.dim_size(0); ++i) {
      num_batches *= output_shape.dim_size(i);
    }
    const int64 num_elements = num_batches * samples_per_batch;

    Tensor* samples_tensor;
    OP_REQUIRES_OK(ctx, ctx->allocate_output(0, output_shape, &samples_tensor));

    auto truncFunctor = functor::TruncatedNormalFunctorV2<Device, T>();
    
    random::PhiloxRandom::Key key;
    random::PhiloxRandom::ResultType counter;
    OP_REQUIRES_OK(ctx, GenerateKey(seed_tensor, &key, &counter));

    auto philox = random::PhiloxRandom(counter, key);

    truncFunctor(ctx, ctx->eigen_device<Device>(), num_batches,
                 samples_per_batch, num_elements, bcast, means_tensor.flat<T>(),
                 stddevs_tensor.flat<T>(), minvals_tensor.flat<T>(),
                 maxvals_tensor.flat<T>(), philox, samples_tensor->flat<T>());
  }