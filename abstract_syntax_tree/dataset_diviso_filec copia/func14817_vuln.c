  void ValidateInputs(OpKernelContext* ctx,
                      const CSRSparseMatrix& sparse_matrix,
                      const Tensor& permutation_indices, int* batch_size,
                      int64* num_rows) {
    OP_REQUIRES(ctx, sparse_matrix.dtype() == DataTypeToEnum<T>::value,
                errors::InvalidArgument(
                    "STR",
                    DataTypeString(DataTypeToEnum<T>::value),
                    "STR", DataTypeString(sparse_matrix.dtype())));

    const Tensor& dense_shape = sparse_matrix.dense_shape();
    const int rank = dense_shape.dim_size(0);
    OP_REQUIRES(ctx, rank == 2 || rank == 3,
                errors::InvalidArgument("STR",
                                        "STR", rank));
    const int row_dim = (rank == 2) ? 0 : 1;
    auto dense_shape_vec = dense_shape.vec<int64>();
    *num_rows = dense_shape_vec(row_dim);
    const int64 num_cols = dense_shape_vec(row_dim + 1);
    OP_REQUIRES(ctx, *num_rows == num_cols,
                errors::InvalidArgument("STR",
                                        *num_rows, "STR", num_cols));
    const TensorShape& perm_shape = permutation_indices.shape();
    OP_REQUIRES(
        ctx, perm_shape.dims() + 1 == rank,
        errors::InvalidArgument(
            "STR", rank,
            "STR"));
    OP_REQUIRES(
        ctx, perm_shape.dim_size(rank - 2) == *num_rows,
        errors::InvalidArgument(
            "STR"
            "STR",
            perm_shape.dim_size(rank - 2), "STR", *num_rows));

    *batch_size = sparse_matrix.batch_size();
    if (*batch_size > 1) {
      OP_REQUIRES(
          ctx, perm_shape.dim_size(0) == *batch_size,
          errors::InvalidArgument("STR"
                                  "STR",
                                  perm_shape.dim_size(0), "STR", *batch_size));
    }
  }