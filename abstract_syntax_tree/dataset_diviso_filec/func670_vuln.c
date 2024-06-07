TfLiteStatus Subgraph::AddNodeWithParameters(
    const std::vector<int>& inputs, const std::vector<int>& outputs,
    const std::vector<int>& intermediates, const char* init_data,
    size_t init_data_size, void* builtin_data,
    const TfLiteRegistration* registration, int* node_index) {
  std::unique_ptr<void, decltype(free)*> builtin_data_deleter(builtin_data,
                                                              free);
  if (state_ == kStateInvokableAndImmutable) {
    ReportError("STR");
    return kTfLiteError;
  }
  state_ = kStateUninvokable;

  TF_LITE_ENSURE_OK(&context_, CheckTensorIndices("STR", inputs.data(),
                                                  inputs.size()));
  TF_LITE_ENSURE_OK(
      &context_,
      CheckTensorIndices("STR", outputs.data(), outputs.size()));

  int new_node_index = nodes_and_registration_.size();
  if (node_index) *node_index = new_node_index;
  nodes_and_registration_.resize(nodes_and_registration_.size() + 1);
  auto& node_and_reg = nodes_and_registration_.back();
  TfLiteNode& node = node_and_reg.first;
  if (node.inputs) TfLiteIntArrayFree(node.inputs);
  if (node.outputs) TfLiteIntArrayFree(node.outputs);
  if (node.intermediates) TfLiteIntArrayFree(node.intermediates);
  if (node.temporaries) TfLiteIntArrayFree(node.temporaries);

  
  
  
  node.inputs = ConvertVectorToTfLiteIntArray(inputs);
  node.outputs = ConvertVectorToTfLiteIntArray(outputs);
  node.intermediates = ConvertVectorToTfLiteIntArray(intermediates);
  node.temporaries = TfLiteIntArrayCreate(0);
  if (init_data) {
    node.user_data = OpInit(*registration, init_data, init_data_size);
  } else {
    node.user_data = OpInit(
        *registration, static_cast<const char*>(builtin_data_deleter.get()), 0);
  }

  node.builtin_data = builtin_data_deleter.release();
  
  

  if (registration->builtin_code == BuiltinOperator_CUSTOM) {
    
    
    node.custom_initial_data = init_data;
    node.custom_initial_data_size = init_data_size;
  } else {
    node.custom_initial_data = nullptr;
    node.custom_initial_data_size = 0;
  }

  node.delegate = nullptr;
  
  node_and_reg.second = *registration;
  execution_plan_.push_back(new_node_index);
  return kTfLiteOk;
}