  bool IsSupported(const NodeDef* node) const override {
    return IsAnyMul(*node) && node->input(0) == node->input(1);
  }