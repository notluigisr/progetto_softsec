  void collectDecls(ESTree::Node *V) {
    if (auto VD = llvh::dyn_cast<ESTree::VariableDeclaratorNode>(V)) {
      return decls.push_back(VD);
    }

    if (auto FD = llvh::dyn_cast<ESTree::FunctionDeclarationNode>(V)) {
      return closures.push_back(FD);
    }
  }