  void Compute(OpKernelContext* context) override {
    ReshapeSparseTensor<Device>(context, context->input(0), context->input(1),
                                context->input(2), 0 ,
                                1 );
  }