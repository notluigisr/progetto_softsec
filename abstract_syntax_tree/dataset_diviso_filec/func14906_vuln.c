  void Compute(OpKernelContext* const context) override {
    
    const Tensor* node_ids_t;
    OP_REQUIRES_OK(context, context->input("STR", &node_ids_t));
    const auto node_ids = node_ids_t->vec<int32>();
    
    const Tensor* gradients_t;
    OP_REQUIRES_OK(context, context->input("STR", &gradients_t));
    const auto gradients = gradients_t->matrix<float>();
    
    const Tensor* hessians_t;
    OP_REQUIRES_OK(context, context->input("STR", &hessians_t));
    const auto hessians = hessians_t->matrix<float>();
    
    OpInputList bucketized_features_list;
    OP_REQUIRES_OK(context, context->input_list("STR",
                                                &bucketized_features_list));
    
    const int64_t batch_size = node_ids_t->dim_size(0);

    
    Tensor temp_stats_double_t;
    OP_REQUIRES_OK(context, context->allocate_temp(
                                DT_DOUBLE,
                                {num_features_, max_splits_, num_buckets_, 2},
                                &temp_stats_double_t));
    auto temp_stats_double = temp_stats_double_t.tensor<double, 4>();
    temp_stats_double.setZero();

    
    for (int feature_idx = 0; feature_idx < num_features_; ++feature_idx) {
      const auto& features = bucketized_features_list[feature_idx].vec<int32>();
      for (int i = 0; i < batch_size; ++i) {
        const int32_t node = node_ids(i);
        const int32_t bucket = features(i);
        temp_stats_double(feature_idx, node, bucket, 0) += gradients(i, 0);
        temp_stats_double(feature_idx, node, bucket, 1) += hessians(i, 0);
      }
    }

    
    Tensor* output_stats_summary_t = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(
                                "STR", temp_stats_double_t.shape(),
                                &output_stats_summary_t));
    output_stats_summary_t->tensor<float, 4>() =
        temp_stats_double.template cast<float>();
  }