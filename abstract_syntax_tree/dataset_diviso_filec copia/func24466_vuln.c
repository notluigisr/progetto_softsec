Status ValidateInputs(const Tensor *a_indices, const Tensor *a_values,
                      const Tensor *a_shape, const Tensor *b) {
  if (!TensorShapeUtils::IsMatrix(a_indices->shape())) {
    return errors::InvalidArgument(
        "STR",
        a_indices->shape().DebugString());
  }
  if (!TensorShapeUtils::IsVector(a_values->shape()) ||
      !TensorShapeUtils::IsVector(a_shape->shape())) {
    return errors::InvalidArgument(
        "STR"
        "STR",
        a_values->shape().DebugString(), "STR",
        a_shape->shape().DebugString());
  }
  if (a_shape->NumElements() != b->dims()) {
    return errors::InvalidArgument(
        "STR", a_shape->NumElements(),
        "STR", b->dims());
  }
  const auto a_shape_flat = a_shape->flat<Index>();
  for (int i = 0; i < b->dims(); ++i) {
    if (a_shape_flat(i) != b->dim_size(i)) {
      return errors::InvalidArgument(
          "STR", i,
          "STR",
          a_shape_flat(i), "STR", b->dim_size(i));
    }
  }
  return Status::OK();
}