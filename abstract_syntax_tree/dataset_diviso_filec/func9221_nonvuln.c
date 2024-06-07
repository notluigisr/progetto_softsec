void ClientConnectionImpl::dumpAdditionalState(std::ostream& os, int indent_level) const {
  const char* spaces = spacesForLevel(indent_level);
  
  if (absl::holds_alternative<ResponseHeaderMapPtr>(headers_or_trailers_)) {
    DUMP_DETAILS(absl::get<ResponseHeaderMapPtr>(headers_or_trailers_));
  } else {
    DUMP_DETAILS(absl::get<ResponseTrailerMapPtr>(headers_or_trailers_));
  }

  
  os << spaces << "STR";
  if (pending_response_.has_value()) {
    os << '\n';
    const ResponseDecoder* decoder = pending_response_.value().decoder_;
    DUMP_DETAILS(decoder);
  } else {
    os << "STR";
  }
}