void FindConstantFoldableNodes(
    const Graph* graph, const ConstantFoldingOptions& opts,
    std::vector<Node*>* nodes,
    std::unordered_map<const Node*, gtl::FlatSet<Node*>>* constant_control_deps,
    std::unordered_map<const Node*, std::vector<Tensor>>*
        shape_replacement_map) {
  bool internal_node_inserted = false;
  
  ReverseDFS(
      *graph, nullptr,
      [nodes, constant_control_deps, shape_replacement_map,
       &internal_node_inserted, &opts](Node* n) {
        ConsiderConstantFoldableNode(n, opts, nodes, constant_control_deps,
                                     shape_replacement_map,
                                     &internal_node_inserted);
      },
      NodeComparatorName());
  
  if (!internal_node_inserted) {
    nodes->clear();
    constant_control_deps->clear();
  }
}