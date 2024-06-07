  Status check_index_ordering(const Tensor& indices) {
    auto findices = indices.flat<int>();

    for (std::size_t i = 0; i < findices.dimension(0) - 1; ++i) {
      if (findices(i) < findices(i + 1)) {
        continue;
      }

      return Status(
          errors::InvalidArgument("STR"));
    }

    return Status::OK();
  }