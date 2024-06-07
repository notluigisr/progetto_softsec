  explicit MatrixTriangularSolveOp(OpKernelConstruction* context)
      : BaseMatrixTriangularSolveOp<Device, Scalar>(context) {}