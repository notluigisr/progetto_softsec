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

    
    const Tensor* feature_t;
    OP_REQUIRES_OK(context, context->input("STR", &feature_t));
    const auto feature = feature_t->matrix<int32>();

    
    const int64_t batch_size = node_ids_t->dim_size(0);
    const int64_t logits_dims = gradients_t->dim_size(1);
    const int64_t hessians_dims = hessians_t->dim_size(1);
    const int64_t stats_dims = logits_dims + hessians_dims;
    const int64_t feature_dims = feature_t->dim_size(1);

    
    
    Tensor temp_stats_double_t;
    OP_REQUIRES_OK(
        context, context->allocate_temp(
                     DT_DOUBLE,
                     {max_splits_, feature_dims, num_buckets_ + 1, stats_dims},
                     &temp_stats_double_t));
    auto temp_stats_double = temp_stats_double_t.tensor<double, 4>();
    temp_stats_double.setZero();

    for (int i = 0; i < batch_size; ++i) {
      const int32_t node = node_ids(i);
      for (int feature_dim = 0; feature_dim < feature_dims; ++feature_dim) {
        const int32_t feature_value = feature(i, feature_dim);
        const int32_t bucket =
            (feature_value == -1) ? num_buckets_ : feature_value;
        for (int stat_dim = 0; stat_dim < logits_dims; ++stat_dim) {
          temp_stats_double(node, feature_dim, bucket, stat_dim) +=
              gradients(i, stat_dim);
        }
        for (int stat_dim = logits_dims; stat_dim < stats_dims; ++stat_dim) {
          temp_stats_double(node, feature_dim, bucket, stat_dim) +=
              hessians(i, stat_dim - logits_dims);
        }
      }
    }

    
    Tensor* output_stats_summary_t = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(
                                "STR", temp_stats_double_t.shape(),
                                &output_stats_summary_t));
    output_stats_summary_t->tensor<float, 4>() =
        temp_stats_double.template cast<float>();
  }