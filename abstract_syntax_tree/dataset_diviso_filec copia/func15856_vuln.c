      TF_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    auto findices = indices.flat<int>();

    
    auto it = incomplete_.find(key);

    
    std::size_t tuple_bytes = get_tuple_bytes(*tuple);
    TF_RETURN_IF_ERROR(check_memory_limit(tuple_bytes));

    
    while (would_exceed_memory_limit(tuple_bytes)) {
      full_.wait(*lock);
    }

    
    
    if (it == incomplete_.end()) {
      OptionalTuple empty(dtypes_.size());

      
      for (std::size_t i = 0; i < findices.dimension(0); ++i) {
        std::size_t index = findices(i);
        TF_RETURN_IF_ERROR(check_index(key, index));

        
        empty[index] = std::move((*tuple)[i]);
      }

      
      incomplete_.insert({key, std::move(empty)});

      
      current_bytes_ += tuple_bytes;
    }
    
    
    
    else {
      
      OptionalTuple& present = it->second;

      
      for (std::size_t i = 0; i < findices.dimension(0); ++i) {
        std::size_t index = findices(i);
        TF_RETURN_IF_ERROR(check_index(key, index));
        TF_RETURN_IF_ERROR(check_index_uninitialized(key, index, present));

        
        present[index] = std::move((*tuple)[i]);
      }

      
      current_bytes_ += tuple_bytes;

      
      bool complete =
          std::all_of(present.begin(), present.end(),
                      [](const OptionalTensor& v) { return v.has_value(); });

      
      if (complete) {
        OptionalTuple insert_tuple = std::move(it->second);

        
        incomplete_.erase(it);

        TF_RETURN_IF_ERROR(put_complete(key, &insert_tuple));
      }
    }

    return Status::OK();
  }