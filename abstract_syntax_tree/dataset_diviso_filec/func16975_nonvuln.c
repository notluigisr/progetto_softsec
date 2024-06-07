port::StatusOr<bool> UseTensorOps(Stream* stream, dnn::DataType type,
                                  absl::optional<dnn::AlgorithmDesc> desc) {
  bool use_tensor_ops;
  if (desc.has_value()) {
    use_tensor_ops = desc->tensor_ops_enabled();
    if (use_tensor_ops && !IsTensorMathEnabled(stream, type)) {
      return port::Status(port::error::INVALID_ARGUMENT,
                          "STR");
    }
  } else {
    use_tensor_ops = IsTensorMathEnabled(stream, type);
  }
  return use_tensor_ops;
}