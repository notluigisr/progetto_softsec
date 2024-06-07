Status Examples::Initialize(OpKernelContext* const context,
                            const ModelWeights& weights,
                            const int num_sparse_features,
                            const int num_sparse_features_with_values,
                            const int num_dense_features) {
  num_features_ = num_sparse_features + num_dense_features;

  OpInputList sparse_example_indices_inputs;
  TF_RETURN_IF_ERROR(context->input_list("STR",
                                         &sparse_example_indices_inputs));
  if (sparse_example_indices_inputs.size() != num_sparse_features)
    return errors::InvalidArgument(
        "STR", num_sparse_features,
        "STR",
        sparse_example_indices_inputs.size());
  OpInputList sparse_feature_indices_inputs;
  TF_RETURN_IF_ERROR(context->input_list("STR",
                                         &sparse_feature_indices_inputs));
  if (sparse_feature_indices_inputs.size() != num_sparse_features)
    return errors::InvalidArgument(
        "STR", num_sparse_features,
        "STR",
        sparse_feature_indices_inputs.size());
  OpInputList sparse_feature_values_inputs;
  if (num_sparse_features_with_values > 0) {
    TF_RETURN_IF_ERROR(context->input_list("STR",
                                           &sparse_feature_values_inputs));
    if (sparse_feature_values_inputs.size() != num_sparse_features_with_values)
      return errors::InvalidArgument(
          "STR", num_sparse_features_with_values,
          "STR",
          sparse_feature_values_inputs.size());
  }

  const Tensor* example_weights_t;
  TF_RETURN_IF_ERROR(context->input("STR", &example_weights_t));
  auto example_weights = example_weights_t->flat<float>();

  if (example_weights.size() >= std::numeric_limits<int>::max()) {
    return errors::InvalidArgument(strings::Printf(
        "STR", example_weights.size(),
        std::numeric_limits<int>::max()));
  }

  
  const int num_examples = static_cast<int>(example_weights.size());
  const Tensor* example_labels_t;
  TF_RETURN_IF_ERROR(context->input("STR", &example_labels_t));
  auto example_labels = example_labels_t->flat<float>();

  OpInputList dense_features_inputs;
  TF_RETURN_IF_ERROR(
      context->input_list("STR", &dense_features_inputs));

  examples_.clear();
  examples_.resize(num_examples);
  probabilities_.resize(num_examples);
  sampled_index_.resize(num_examples);
  sampled_count_.resize(num_examples);
  for (int example_id = 0; example_id < num_examples; ++example_id) {
    Example* const example = &examples_[example_id];
    example->sparse_features_.resize(num_sparse_features);
    example->dense_vectors_.resize(num_dense_features);
    example->example_weight_ = example_weights(example_id);
    example->example_label_ = example_labels(example_id);
  }
  const DeviceBase::CpuWorkerThreads& worker_threads =
      *context->device()->tensorflow_cpu_worker_threads();
  TF_RETURN_IF_ERROR(CreateSparseFeatureRepresentation(
      worker_threads, num_examples, num_sparse_features, weights,
      sparse_example_indices_inputs, sparse_feature_indices_inputs,
      sparse_feature_values_inputs, &examples_));
  TF_RETURN_IF_ERROR(CreateDenseFeatureRepresentation(
      worker_threads, num_examples, num_dense_features, weights,
      dense_features_inputs, &examples_));
  TF_RETURN_IF_ERROR(ComputeSquaredNormPerExample(
      worker_threads, num_examples, num_sparse_features, num_dense_features,
      &examples_));
  return Status::OK();
}