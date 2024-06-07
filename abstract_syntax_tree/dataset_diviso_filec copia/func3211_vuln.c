static Status ValidateSavedTensors(const GraphDef& graph_def) {
  for (const auto& node : graph_def.node()) {
    const auto node_iterator = node.attr().find("STR");
    if (node_iterator != node.attr().end()) {
      AttrValue node_value = node_iterator->second;
      if (node_value.has_tensor()) {
        const PartialTensorShape node_shape(node_value.tensor().tensor_shape());
        if (node_shape.num_elements() < 0) {
          return errors::FailedPrecondition(
              "STR",
              node.op(), "STR",
              node_shape.num_elements(), "STR");
        }
      }
    } else if (node.op() == "STR") {
      return errors::FailedPrecondition(
          "STR", node.name(),
          "STR");
    }
  }
  return Status::OK();
}