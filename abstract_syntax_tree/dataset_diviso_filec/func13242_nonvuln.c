  explicit UnsortedSegmentReductionOp(OpKernelConstruction* context)
      : OpKernel(context), reduction_functor_(DeviceReductionFunctor()) {}