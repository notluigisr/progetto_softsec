  void Compute(OpKernelContext* context) override {
    const Tensor& prefix = context->input(0);
    const Tensor& tensor_names = context->input(1);
    const Tensor& shape_and_slices = context->input(2);
    OP_REQUIRES(context, tensor_names.NumElements() == dtypes_.size(),
                errors::InvalidArgument("STR", tensor_names.NumElements(),
                                        "STR", dtypes_.size(),
                                        "STR"));
    ValidateInputs(false , context, prefix, tensor_names,
                   shape_and_slices);

    const string& prefix_string = prefix.scalar<tstring>()();

    
    
    
    
    Env* env = Env::Default();
    std::vector<string> paths;
    if (!env->GetMatchingPaths(MetaFilename(prefix_string), &paths).ok() ||
        paths.empty()) {
      
      
      for (size_t i = 0; i < tensor_names.NumElements(); ++i) {
        RestoreTensor(context, &checkpoint::OpenTableTensorSliceReader,
                       -1,  true,
                       i);
        if (!context->status().ok()) {
          return;
        }
      }
      return;
    }
    
    OP_REQUIRES_OK(context, RestoreTensorsV2(context, prefix, tensor_names,
                                             shape_and_slices, dtypes_));
  }