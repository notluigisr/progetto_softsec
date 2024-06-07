  bool IsAbsorbableByOptimizedNodesGroup(const OptimizedNodesGroup& group,
                                         const NodeDef& node) const override {
    if (!IsSameOp(group, node)) {
      return false;
    }
    if (IsInPreserveSet(node)) {
      return false;
    }
    
    if (IsMarkedWithAnyTag(node, kMinimizeBroadcastsTag, kAddOpsRewriteTag)) {
      return false;
    }
    if (IsDrivenByControlDependency(node) || DrivesControlDependency(node)) {
      return false;
    }
    if (!IsOnTheSameDevice(group, node)) {
      return false;
    }
    
    
    if (NumNonControlOutputs(node, *ctx().node_map) != 1) {
      return false;
    }
    
    const OpInfo::TensorProperties* properties;
    Status has_properties = GetTensorProperties(node.name(), &properties);
    return has_properties.ok() &&
           HasAllInputsBroadcastableToShape(node, *properties);
  }