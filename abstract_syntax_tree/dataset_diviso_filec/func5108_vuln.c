  void AddBatchOffsets(Tensor* indices, const Tensor& params) {
    int64_t batch_size = 1;  
    for (int idx = 0; idx < batch_dims_; ++idx) {
      batch_size *= params.dim_size(idx);
    }

    auto indices_flat = indices->flat<Index>();
    int64_t const index_inner_size = indices->NumElements() / batch_size;
    int64_t const batch_offset = params.dim_size(batch_dims_);
    for (int64_t batch_idx = 0, dest_idx = 0; batch_idx < batch_size;
         ++batch_idx) {
      for (int64_t idx = 0; idx < index_inner_size; ++idx) {
        indices_flat(dest_idx++) += batch_offset * batch_idx;
      }
    }
  }