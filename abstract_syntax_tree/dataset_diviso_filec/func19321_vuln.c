  void Compute(OpKernelContext* context) override {
    
    const Tensor* stamp_token_t;
    OP_REQUIRES_OK(context, context->input("STR", &stamp_token_t));
    int64_t stamp_token = stamp_token_t->scalar<int64>()();

    
    const Tensor* tree_ensemble_serialized_t;
    OP_REQUIRES_OK(context, context->input("STR",
                                           &tree_ensemble_serialized_t));
    std::unique_ptr<BoostedTreesEnsembleResource> result(
        new BoostedTreesEnsembleResource());
    if (!result->InitFromSerialized(
            tree_ensemble_serialized_t->scalar<tstring>()(), stamp_token)) {
      result->Unref();
      OP_REQUIRES(
          context, false,
          errors::InvalidArgument("STR"));
    }

    
    
    auto status =
        CreateResource(context, HandleFromInput(context, 0), result.release());
    if (status.code() != tensorflow::error::ALREADY_EXISTS) {
      OP_REQUIRES_OK(context, status);
    }
  }