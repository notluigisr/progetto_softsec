  void Compute(OpKernelContext* context) override {
    const Tensor& indices = context->input(0);
    const Tensor& values = context->input(1);
    const Tensor& shape = context->input(2);
    const Tensor& weights = context->input(3);
    bool use_weights = weights.NumElements() > 0;

    bool is_1d = shape.NumElements() == 1;
    int num_batches = is_1d ? 1 : shape.flat<int64>()(0);
    int num_values = values.NumElements();

    const auto indices_values = indices.matrix<int64>();
    const auto values_values = values.flat<T>();
    const auto weight_values = weights.flat<W>();

    auto per_batch_counts = BatchedMap<W>(num_batches);

    T max_value = 0;

    for (int idx = 0; idx < num_values; ++idx) {
      int batch = is_1d ? 0 : indices_values(idx, 0);
      const auto& value = values_values(idx);
      if (value >= 0 && (maxlength_ <= 0 || value < maxlength_)) {
        if (binary_output_) {
          per_batch_counts[batch][value] = 1;
        } else if (use_weights) {
          per_batch_counts[batch][value] += weight_values(idx);
        } else {
          per_batch_counts[batch][value]++;
        }
        if (value > max_value) {
          max_value = value;
        }
      }
    }

    int num_output_values = GetOutputSize(max_value, maxlength_, minlength_);
    OP_REQUIRES_OK(context, OutputSparse<W>(per_batch_counts, num_output_values,
                                            is_1d, context));
  }