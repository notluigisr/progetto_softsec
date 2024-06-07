      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (index >= dtypes_.size()) {
      return Status(errors::InvalidArgument(
          "STR", key.scalar<int64>()(),
          "STR"));
    }

    return Status::OK();
  }