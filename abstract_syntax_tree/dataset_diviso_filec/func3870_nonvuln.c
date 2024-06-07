ArrayMap<Scalar> MapAsArrayWithLastDimAsRows(Scalar* data,
                                             const RuntimeShape& shape) {
  const int dims_count = shape.DimensionsCount();
  const int rows = shape.Dims(dims_count - 1);
  const int cols = FlatSizeSkipDim(shape, dims_count - 1);
  return ArrayMap<Scalar>(data, rows, cols);
}