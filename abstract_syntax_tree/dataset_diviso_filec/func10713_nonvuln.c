static void SegmentReductionValidationHelper(OpKernelContext* context,
                                             const Tensor& input,
                                             const Tensor& segment_ids) {
  OP_REQUIRES(context, TensorShapeUtils::IsVector(segment_ids.shape()),
              errors::InvalidArgument("STR"));
  const int64 num_indices = segment_ids.NumElements();
  OP_REQUIRES(context, num_indices == input.dim_size(0),
              errors::InvalidArgument(
                  "STR"
                  "STR"));
}