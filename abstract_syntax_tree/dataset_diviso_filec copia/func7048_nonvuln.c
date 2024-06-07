  explicit SparseSegmentReductionSqrtNWithNumSegmentsOp(
      OpKernelConstruction* context)
      : SparseSegmentReductionOpBase<Device, T>(
            context, false , true ,
            true , T(0) ) {}