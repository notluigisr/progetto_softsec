      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (tuple[index].has_value()) {
      return Status(errors::InvalidArgument(
          "STR", key.scalar<int64>()(),
          "STR"));
    }

    return Status::OK();
  }