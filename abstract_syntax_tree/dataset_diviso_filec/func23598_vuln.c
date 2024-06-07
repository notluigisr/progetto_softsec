  void Compute(OpKernelContext* ctx) override {
    const Tensor& handle = ctx->input(0);
    const string& name = handle.scalar<tstring>()();
    Tensor val;
    OP_REQUIRES_OK(ctx, ctx->session_state()->GetTensor(name, &val));
    ctx->set_output(0, val);
  }