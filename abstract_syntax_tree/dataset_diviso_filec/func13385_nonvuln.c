void ActiveStreamEncoderFilter::sendLocalReply(
    Code code, absl::string_view body,
    std::function<void(ResponseHeaderMap& headers)> modify_headers,
    const absl::optional<Grpc::Status::GrpcStatus> grpc_status, absl::string_view details) {
  parent_.sendLocalReply(code, body, modify_headers, grpc_status, details);
}