  void Compute(OpKernelContext* context) override {
    OpInputList indices_list_in;
    OP_REQUIRES_OK(context, context->input_list("STR", &indices_list_in));
    OpInputList values_list_in;
    OP_REQUIRES_OK(context, context->input_list("STR", &values_list_in));
    OpInputList shapes_list_in;
    OP_REQUIRES_OK(context, context->input_list("STR", &shapes_list_in));
    OpInputList dense_list_in;
    OP_REQUIRES_OK(context,
                   context->input_list("STR", &dense_list_in));

    OP_REQUIRES_OK(context, ValidateInput(indices_list_in, values_list_in,
                                          shapes_list_in, dense_list_in));

    const Tensor* num_buckets_t;
    OP_REQUIRES_OK(context, context->input("STR", &num_buckets_t));
    const int64 num_buckets = num_buckets_t->scalar<int64>()();

    const Tensor* strong_hash_t;
    OP_REQUIRES_OK(context, context->input("STR", &strong_hash_t));
    const bool strong_hash = strong_hash_t->scalar<bool>()();

    const Tensor* salt_t;
    OP_REQUIRES_OK(context, context->input("STR", &salt_t));
    const auto salt = salt_t->flat<int64>();
    std::vector<int64> key_{salt(0), salt(1)};

    std::vector<std::unique_ptr<ColumnInterface<int64>>> columns =
        GenerateKeyedColumnsFromInput<int64>(indices_list_in, values_list_in,
                                             shapes_list_in, dense_list_in,
                                             key_);
    Tensor* indices_out;
    Tensor* values_out;
    Tensor* shape_out;
    const int64 batch_size = CalculateBatchSize(shapes_list_in, dense_list_in);
    std::vector<int64> output_start_indices(batch_size);
    OP_REQUIRES_OK(
        context,
        CreateOutputTensors(columns, batch_size, context, &indices_out,
                            &values_out, &shape_out, &output_start_indices));
    const tstring unused_sep;
    HashCrosserV2 crosser(columns, num_buckets, 0, unused_sep);
    OutputUpdater<int64> updater(output_start_indices, indices_out, values_out);
    auto do_work = [&columns, crosser, updater, strong_hash](int64 begin,
                                                             int64 end) {
      for (int b = begin; b < end; b++) {
        ProductIterator<int64> product_iterator(columns, b);
        int64 cross_count = 0;
        while (product_iterator.HasNext()) {
          const auto permutation = product_iterator.Next();
          updater.Update(b, cross_count,
                         crosser.Generate(b, permutation, strong_hash));
          cross_count++;
        }
      }
    };

    auto* worker_threads = context->device()->tensorflow_cpu_worker_threads();
    
    const int kCostPerUnit = 5000 * indices_list_in.size();
    Shard(worker_threads->num_threads, worker_threads->workers, batch_size,
          kCostPerUnit, do_work);
  }