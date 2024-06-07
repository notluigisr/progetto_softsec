  void Compute(OpKernelContext* context) override {
    const Tensor* reverse_index_map_t;
    const Tensor* grad_values_t;
    OP_REQUIRES_OK(context,
                   context->input("STR", &reverse_index_map_t));
    OP_REQUIRES_OK(context, context->input("STR", &grad_values_t));

    const CPUDevice& d = context->eigen_device<CPUDevice>();

    OP_REQUIRES(
        context, TensorShapeUtils::IsVector(reverse_index_map_t->shape()),
        errors::InvalidArgument("STR",
                                reverse_index_map_t->shape().DebugString()));

    const auto reverse_index_map = reverse_index_map_t->vec<int64>();
    const auto grad_values = grad_values_t->vec<T>();

    const int64 N = reverse_index_map_t->shape().dim_size(0);
    const int64 N_full = grad_values_t->shape().dim_size(0);

    Tensor* d_values_t;
    OP_REQUIRES_OK(context, context->allocate_output(
                                "STR", TensorShape({N}), &d_values_t));
    auto d_values = d_values_t->vec<T>();
    Tensor* d_default_value_t;
    OP_REQUIRES_OK(context,
                   context->allocate_output("STR", TensorShape({}),
                                            &d_default_value_t));
    T& d_default_value = d_default_value_t->scalar<T>()();
    d_default_value = T();

    Tensor visited_t;
    OP_REQUIRES_OK(context, context->allocate_temp(
                                DT_BOOL, TensorShape({N_full}), &visited_t));
    auto visited = visited_t.vec<bool>();
    visited.device(d) = visited.constant(false);

    for (int i = 0; i < N; ++i) {
      
      
      
      d_values(i) = grad_values(reverse_index_map(i));
      visited(reverse_index_map(i)) = true;
    }
    for (int j = 0; j < N_full; ++j) {
      
      
      
      if (!visited(j)) {
        d_default_value += grad_values(j);
      }
    }
  }