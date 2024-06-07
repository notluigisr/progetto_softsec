int ConnectionImpl::onHeadersCompleteBase() {
  ENVOY_CONN_LOG(trace, "STR", connection_);
  completeLastHeader();
  if (!(parser_.http_major == 1 && parser_.http_minor == 1)) {
    
    
    protocol_ = Protocol::Http10;
  }
  if (Utility::isUpgrade(*current_header_map_)) {
    
    
    if (current_header_map_->Upgrade() &&
        absl::EqualsIgnoreCase(current_header_map_->Upgrade()->value().getStringView(),
                               Http::Headers::get().UpgradeValues.H2c)) {
      ENVOY_CONN_LOG(trace, "STR", connection_);
      current_header_map_->removeUpgrade();
      if (current_header_map_->Connection()) {
        const auto& tokens_to_remove = caseUnorderdSetContainingUpgradeAndHttp2Settings();
        std::string new_value = StringUtil::removeTokens(
            current_header_map_->Connection()->value().getStringView(), "STR");
        if (new_value.empty()) {
          current_header_map_->removeConnection();
        } else {
          current_header_map_->Connection()->value(new_value);
        }
      }
      current_header_map_->remove(Headers::get().Http2Settings);
    } else {
      ENVOY_CONN_LOG(trace, "STR", connection_);
      handling_upgrade_ = true;
    }
  }

  int rc = onHeadersComplete(std::move(current_header_map_));
  current_header_map_.reset();
  header_parsing_state_ = HeaderParsingState::Done;

  
  return handling_upgrade_ ? 2 : rc;
}