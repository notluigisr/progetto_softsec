TfLiteStatus Subgraph::PrepareOpsStartingAt(
    int first_execution_plan_index, const std::vector<int>& execution_plan,
    int* last_execution_plan_index_prepared) {
  if (first_execution_plan_index == 0) {
    has_dynamic_tensors_ = false;
  }
  for (int execution_plan_index = first_execution_plan_index;
       execution_plan_index < execution_plan.size(); execution_plan_index++) {
    int node_index = execution_plan[execution_plan_index];
    TfLiteNode& node = nodes_and_registration_[node_index].first;
    const TfLiteRegistration& registration =
        nodes_and_registration_[node_index].second;
    EnsureTensorsVectorCapacity();
    if (OpPrepare(registration, &node) != kTfLiteOk) {
      return ReportOpError(&context_, node, registration, node_index,
                           "STR");
    }

    *last_execution_plan_index_prepared = execution_plan_index;

    
    
    
    if (HasDynamicTensor(context_, node.outputs)) {
      has_dynamic_tensors_ = true;
      return kTfLiteOk;
    }
  }
  return kTfLiteOk;
}