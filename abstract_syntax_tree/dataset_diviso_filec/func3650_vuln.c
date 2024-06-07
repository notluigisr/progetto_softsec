std::pair<Function *, Function *> ESTreeIRGen::doLazyFunction(
    hbc::LazyCompilationData *lazyData) {
  
  
  
  Function *topLevel = Builder.createTopLevelFunction(lazyData->strictMode, {});

  FunctionContext topLevelFunctionContext{this, topLevel, nullptr};

  
  
  llvh::SaveAndRestore<FunctionContext *> saveTopLevelContext(
      topLevelContext, &topLevelFunctionContext);

  auto *node = cast<ESTree::FunctionLikeNode>(Root);

  
  
  
  
  
  
  
  lexicalScopeChain = lazyData->parentScope;
  materializeScopesInChain(
      topLevel, lexicalScopeChain, getDepth(lexicalScopeChain) - 1);

  
  
  
  Variable *parentVar = nullptr;
  if (lazyData->closureAlias.isValid()) {
    assert(lazyData->originalName.isValid() && "STR");
    assert(
        lazyData->originalName != lazyData->closureAlias &&
        "STR");

    
    parentVar = cast<Variable>(nameTable_.lookup(lazyData->closureAlias));

    
    nameTable_.insert(lazyData->originalName, parentVar);
  }

  assert(
      !llvh::isa<ESTree::ArrowFunctionExpressionNode>(node) &&
      "STR");

  auto *func = genES5Function(lazyData->originalName, parentVar, node);
  addLexicalDebugInfo(func, topLevel, lexicalScopeChain);
  return {func, topLevel};
}