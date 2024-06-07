void FilterManager::encodeMetadata(ActiveStreamEncoderFilter* filter,
                                   MetadataMapPtr&& metadata_map_ptr) {
  filter_manager_callbacks_.resetIdleTimer();

  std::list<ActiveStreamEncoderFilterPtr>::iterator entry =
      commonEncodePrefix(filter, false, FilterIterationStartState::CanStartFromCurrent);

  for (; entry != encoder_filters_.end(); entry++) {
    if ((*entry)->skipFilter()) {
      continue;
    }
    
    
    
    
    if (!(*entry)->encode_headers_called_ || (*entry)->stoppedAll()) {
      (*entry)->getSavedResponseMetadata()->emplace_back(std::move(metadata_map_ptr));
      return;
    }

    FilterMetadataStatus status = (*entry)->handle_->encodeMetadata(*metadata_map_ptr);
    ENVOY_STREAM_LOG(trace, "STR", *this,
                     static_cast<const void*>((*entry).get()), static_cast<uint64_t>(status));
  }
  

  
  if (!metadata_map_ptr->empty()) {
    MetadataMapVector metadata_map_vector;
    metadata_map_vector.emplace_back(std::move(metadata_map_ptr));
    filter_manager_callbacks_.encodeMetadata(metadata_map_vector);
  }
}