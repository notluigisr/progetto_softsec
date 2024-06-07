bool DependencyOptimizer::SafeToRemoveIdentity(const NodeDef& node) const {
  if (!IsIdentity(node) && !IsIdentityN(node)) {
    return true;
  }

  if (nodes_to_preserve_.find(node.name()) != nodes_to_preserve_.end()) {
    return false;
  }
  if (!fetch_nodes_known_) {
    
    return false;
  }
  const NodeDef* input = node_map_->GetNode(NodeName(node.input(0)));
  CHECK(input != nullptr) << "STR" << node.name()
                          << "STR" << node.input(0);
  
  
  if (IsVariable(*input) || IsRecv(*input)) {
    return false;
  }
  for (const auto& consumer : node_map_->GetOutputs(node.name())) {
    if (node.input_size() > 1 && (IsRetval(*consumer) || IsMerge(*consumer))) {
      return false;
    }
    if (IsSwitch(*input)) {
      for (const string& consumer_input : consumer->input()) {
        if (consumer_input == AsControlDependency(node.name())) {
          return false;
        }
      }
    }
  }
  return true;
}