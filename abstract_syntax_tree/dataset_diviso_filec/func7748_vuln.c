  void Compute(OpKernelContext* ctx) override {
    StagingMap<Ordered>* map = nullptr;
    OP_REQUIRES_OK(ctx, GetStagingMap(ctx, def(), &map));
    core::ScopedUnref scope(map);
    typename StagingMap<Ordered>::OptionalTuple tuple;

    const Tensor* key_tensor;
    const Tensor* indices_tensor;
    OpInputList values_tensor;

    OP_REQUIRES_OK(ctx, ctx->input("STR", &key_tensor));
    OP_REQUIRES_OK(ctx, ctx->input("STR", &indices_tensor));
    OP_REQUIRES_OK(ctx, ctx->input_list("STR", &values_tensor));

    
    Tensor key(*key_tensor);

    
    for (std::size_t i = 0; i < values_tensor.size(); ++i) {
      tuple.push_back(values_tensor[i]);
    }

    
    OP_REQUIRES_OK(ctx, map->put(&key, indices_tensor, &tuple));
  }