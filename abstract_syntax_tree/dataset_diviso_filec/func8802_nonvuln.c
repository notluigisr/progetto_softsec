static void UnsortedSegmentReductionValidation(OpKernel* op_kernel,
                                               OpKernelContext* context,
                                               const Tensor& data,
                                               const Tensor& segment_ids,
                                               const Tensor& num_segments) {
  OP_REQUIRES(
      context, op_kernel->IsLegacyScalar(num_segments.shape()),
      errors::InvalidArgument("STR",
                              num_segments.shape().DebugString()));
  OP_REQUIRES(
      context, TensorShapeUtils::StartsWith(data.shape(), segment_ids.shape()),
      errors::InvalidArgument("STR", data.shape().DebugString(),
                              "STR",
                              segment_ids.shape().DebugString()));
}