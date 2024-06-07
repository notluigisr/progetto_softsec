      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    
    map_.insert({key, std::move(*tuple)});

    notify_removers();

    return Status::OK();
  }