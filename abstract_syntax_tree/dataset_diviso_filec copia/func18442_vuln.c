Status ValidateShapes(OpKernelContext* ctx, const Tensor& hypothesis_indices,
                      const Tensor& hypothesis_values,
                      const Tensor& hypothesis_shape,
                      const Tensor& truth_indices, const Tensor& truth_values,
                      const Tensor& truth_shape) {
  if (!TensorShapeUtils::IsMatrix(hypothesis_indices.shape()))
    return errors::InvalidArgument(
        "STR",
        hypothesis_indices.shape().DebugString());
  if (!TensorShapeUtils::IsMatrix(truth_indices.shape()))
    return errors::InvalidArgument(
        "STR",
        truth_indices.shape().DebugString());
  if (!TensorShapeUtils::IsVector(hypothesis_values.shape()))
    return errors::InvalidArgument(
        "STR",
        hypothesis_values.shape().DebugString());
  if (!TensorShapeUtils::IsVector(truth_values.shape()))
    return errors::InvalidArgument(
        "STR",
        truth_values.shape().DebugString());
  if (!TensorShapeUtils::IsVector(hypothesis_shape.shape()))
    return errors::InvalidArgument(
        "STR",
        hypothesis_shape.shape().DebugString());
  if (!TensorShapeUtils::IsVector(truth_shape.shape()))
    return errors::InvalidArgument(
        "STR",
        truth_shape.shape().DebugString());
  if (hypothesis_shape.NumElements() != hypothesis_indices.dim_size(1))
    return errors::InvalidArgument(
        "STR"
        "STR",
        hypothesis_shape.shape().DebugString(), "STR",
        hypothesis_indices.shape().DebugString());
  if (truth_shape.NumElements() < 2)
    return errors::InvalidArgument(
        "STR"
        "STR",
        truth_shape.NumElements());
  if (truth_shape.NumElements() != truth_indices.dim_size(1))
    return errors::InvalidArgument(
        "STR"
        "STR",
        truth_shape.shape().DebugString(), "STR",
        truth_indices.shape().DebugString());
  if (truth_shape.NumElements() != hypothesis_shape.NumElements())
    return errors::InvalidArgument(
        "STR"
        "STR",
        truth_shape.shape().DebugString(), "STR",
        hypothesis_shape.shape().DebugString());

  return Status::OK();
}