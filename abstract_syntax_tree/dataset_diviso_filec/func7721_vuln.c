  void MakeDataset(OpKernelContext* ctx, DatasetBase** output) override {
    
    
    const Tensor* indices;
    OP_REQUIRES_OK(ctx, ctx->input("STR", &indices));
    const Tensor* values;
    OP_REQUIRES_OK(ctx, ctx->input("STR", &values));
    const Tensor* dense_shape;
    OP_REQUIRES_OK(ctx, ctx->input("STR", &dense_shape));

    OP_REQUIRES(ctx, TensorShapeUtils::IsMatrix(indices->shape()),
                errors::InvalidArgument(
                    "STR",
                    indices->shape().DebugString()));
    OP_REQUIRES(ctx, TensorShapeUtils::IsVector(values->shape()),
                errors::InvalidArgument(
                    "STR",
                    indices->shape().DebugString()));
    OP_REQUIRES(ctx, TensorShapeUtils::IsVector(dense_shape->shape()),
                errors::InvalidArgument(
                    "STR",
                    dense_shape->shape().DebugString()));

    
    
    
    
    
    
    int64_t previous_batch_index = -1;
    for (int64_t i = 0; i < indices->dim_size(0); ++i) {
      int64_t next_batch_index = indices->matrix<int64>()(i, 0);
      OP_REQUIRES(
          ctx, next_batch_index >= previous_batch_index,
          errors::Unimplemented("STR"
                                "STR"
                                "STR"));
      previous_batch_index = next_batch_index;
    }
    gtl::InlinedVector<int64, 8> std_order(dense_shape->NumElements(), 0);
    sparse::SparseTensor tensor;
    OP_REQUIRES_OK(
        ctx, sparse::SparseTensor::Create(
                 *indices, *values, TensorShape(dense_shape->vec<int64>()),
                 std_order, &tensor));
    *output = new Dataset<T>(ctx, std::move(tensor));
  }