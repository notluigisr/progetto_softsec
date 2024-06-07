Status InferenceContext::AttachContext(const Status& status) {
  std::vector<string> input_shapes;
  input_shapes.reserve(inputs_.size());
  for (const ShapeHandle& input_shape : inputs_) {
    input_shapes.emplace_back(DebugString(input_shape));
  }

  
  std::vector<string> input_from_tensors_str;
  std::vector<string> input_from_tensors_as_shape_str;
  input_from_tensors_as_shape_str.reserve(inputs_.size());
  for (int i = 0, end = inputs_.size(); i < end; ++i) {
    const int input_tensors_as_shapes_size = input_tensors_as_shapes_.size();
    const int input_tensors_size = input_tensors_.size();
    if (requested_input_tensor_as_partial_shape_[i] &&
        i < input_tensors_as_shapes_size &&
        input_tensors_as_shapes_[i].IsSet() &&
        RankKnown(input_tensors_as_shapes_[i])) {
      input_from_tensors_as_shape_str.push_back(strings::StrCat(
          "STR", DebugString(input_tensors_as_shapes_[i])));
    } else if (requested_input_tensor_[i] && i < input_tensors_size &&
               input_tensors_[i] != nullptr) {
      input_from_tensors_str.push_back(strings::StrCat(
          "STR",
          input_tensors_[i]->SummarizeValue(256 ), "STR"));
    }
  }

  string error_context = strings::StrCat(
      "STR", attrs_.SummarizeNode(),
      "STR"));
  if (!input_from_tensors_str.empty()) {
    strings::StrAppend(&error_context, "STR",
                       absl::StrJoin(input_from_tensors_str, "STR"));
  }
  if (!input_from_tensors_as_shape_str.empty()) {
    strings::StrAppend(&error_context,
                       "STR",
                       absl::StrJoin(input_from_tensors_as_shape_str, "STR"));
  }

  strings::StrAppend(&error_context, "STR");
  return errors::CreateWithUpdatedMessage(
      status, strings::StrCat(status.error_message(), error_context));
}