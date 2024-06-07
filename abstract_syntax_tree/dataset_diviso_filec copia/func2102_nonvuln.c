  Status CheckInputs(Tensor group_size_t, Tensor group_key_t) {
    if (group_size_t.dims() > 0) {
      return errors::InvalidArgument(
          "STR"
          "STR",
          group_size_t.shape().DebugString());
    }
    if (group_key_t.dims() > 0) {
      return errors::InvalidArgument(
          "STR",
          group_key_t.shape().DebugString());
    }

    auto group_size = group_size_t.unaligned_flat<int32>()(0);
    if (group_size <= 0) {
      return errors::InvalidArgument(
          "STR", group_size);
    }
    return Status::OK();
  }