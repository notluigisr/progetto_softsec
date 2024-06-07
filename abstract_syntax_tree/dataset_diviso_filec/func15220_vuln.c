  void ComputeAsync(OpKernelContext* c, DoneCallback done) override {
    auto col_params = new CollectiveParams();
    auto done_with_cleanup = [col_params, done = std::move(done)]() {
      done();
      col_params->Unref();
    };
    OP_REQUIRES_OK_ASYNC(c,
                         FillCollectiveParams(col_params, REDUCTION_COLLECTIVE,
                                               c->input(1),
                                               c->input(2),
                                               c->input(3)),
                         done);
    col_params->instance.shape = c->input(0).shape();
    col_params->merge_op = merge_op_.get();
    col_params->final_op = final_op_.get();
    VLOG(1) << "STR" << col_params->group.group_size
            << "STR"
            << col_params->instance.instance_key;
    
    Tensor* output = nullptr;
    OP_REQUIRES_OK_ASYNC(c,
                         c->forward_input_or_allocate_output(
                             {0}, 0, col_params->instance.shape, &output),
                         done_with_cleanup);
    Run(c, col_params, std::move(done_with_cleanup));
  }