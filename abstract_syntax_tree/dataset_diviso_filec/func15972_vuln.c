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

    const Tensor* sep_t;
    OP_REQUIRES_OK(context, context->input("STR", &sep_t));
    const tstring separator = sep_t->scalar<tstring>()();

    std::vector<std::unique_ptr<ColumnInterface<tstring>>> columns =
        GenerateColumnsFromInput<tstring>(indices_list_in, values_list_in,
                                          shapes_list_in, dense_list_in);
    Tensor* indices_out;
    Tensor* values_out;
    Tensor* shape_out;
    const int64 batch_size = CalculateBatchSize(shapes_list_in, dense_list_in);
    std::vector<int64> output_start_indices(batch_size);
    OP_REQUIRES_OK(
        context,
        CreateOutputTensors(columns, batch_size, context, &indices_out,
                            &values_out, &shape_out, &output_start_indices));
    StringCrosser<tstring> crosser(columns, 0, 0, separator);
    OutputUpdater<tstring> updater(output_start_indices, indices_out,
                                   values_out);
    auto do_work = [&columns, crosser, updater](int64 begin, int64 end) {
      for (int b = begin; b < end; b++) {
        ProductIterator<tstring> product_iterator(columns, b);
        int64 cross_count = 0;
        while (product_iterator.HasNext()) {
          const auto permutation = product_iterator.Next();
          updater.Update(b, cross_count,
                         crosser.Generate(b, permutation, false));
          cross_count++;
        }
      }
    };

    auto* worker_threads = context->device()->tensorflow_cpu_worker_threads();
    
    const int kCostPerUnit = 5000 * indices_list_in.size();
    Shard(worker_threads->num_threads, worker_threads->workers, batch_size,
          kCostPerUnit, do_work);
  }