  void Compute(OpKernelContext* context) override {
    
    OpInputList params_nested_splits_in;
    OP_REQUIRES_OK(context, context->input_list("STR",
                                                &params_nested_splits_in));
    const Tensor& params_dense_values_in =
        context->input(params_nested_splits_in.size());
    const Tensor& indices_in =
        context->input(params_nested_splits_in.size() + 1);

    DCHECK_GT(params_nested_splits_in.size(), 0);  
    SPLITS_TYPE num_params = params_nested_splits_in[0].dim_size(0) - 1;
    OP_REQUIRES_OK(context, ValidateIndices(indices_in, num_params));

    OP_REQUIRES(context, params_dense_values_in.dims() > 0,
                errors::InvalidArgument("STR"));
    SPLITS_TYPE num_params_dense_values = params_dense_values_in.dim_size(0);

    
    
    std::vector<std::pair<SPLITS_TYPE, SPLITS_TYPE>> value_slices;
    SPLITS_TYPE num_values = 0;
    std::vector<std::vector<SPLITS_TYPE>> out_splits;
    OP_REQUIRES_OK(context, MakeSplits(indices_in, params_nested_splits_in,
                                       num_params_dense_values, &out_splits,
                                       &value_slices, &num_values));

    
    OP_REQUIRES_OK(context, WriteSplits(out_splits, context));
    OP_REQUIRES_OK(context,
                   WriteValues(params_dense_values_in, value_slices,
                               out_splits.size(), num_values, context));
  }