      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    auto findices = indices.flat<int>();

    
    for (std::size_t i = 0; i < findices.dimension(0); ++i) {
      std::size_t index = findices(i);

      TF_RETURN_IF_ERROR(check_index(key, index));

      
      if (!(*map_tuple)[index].has_value()) {
        return Status(errors::InvalidArgument(
            "STR", key.scalar<int64>()(),
            "STR"));
      }

      
      
      output->push_back((*map_tuple)[index].value());

      
      if (!copy) {
        (*map_tuple)[index].reset();
      }
    }

    return Status::OK();
  }