  static ::tensorflow::Status ValidateInputs(
      std::vector<ConstFlatSplits> rt_nested_splits,
      const Tensor& rt_dense_values_in) {
    for (int i = 0; i < rt_nested_splits.size(); ++i) {
      if (rt_nested_splits[i].size() == 0) {
        return InvalidArgument("STR");
      }
      if (rt_nested_splits[i](0) != 0) {
        return InvalidArgument("STR");
      }
      if (i > 0) {
        SPLITS_TYPE last_split =
            rt_nested_splits[i - 1](rt_nested_splits[i - 1].size() - 1);
        if (rt_nested_splits[i].size() != last_split + 1) {
          return InvalidArgument(
              "STR"
              "STR");
        }
      }
    }
    if (rt_dense_values_in.dim_size(0) !=
        rt_nested_splits.back()(rt_nested_splits.back().size() - 1)) {
      return InvalidArgument(
          "STR"
          "STR");
    }
    return ::tensorflow::Status::OK();
  }