Function *ESTreeIRGen::genGeneratorFunction(
    Identifier originalName,
    Variable *lazyClosureAlias,
    ESTree::FunctionLikeNode *functionNode) {
  assert(functionNode && "STR");

  
  
  auto *outerFn = Builder.createGeneratorFunction(
      originalName,
      Function::DefinitionKind::ES5Function,
      ESTree::isStrict(functionNode->strictness),
       nullptr);

  auto *innerFn = genES5Function(
      genAnonymousLabelName(originalName.isValid() ? originalName.str() : ""),
      lazyClosureAlias,
      functionNode,
      true);

  {
    FunctionContext outerFnContext{this, outerFn, functionNode->getSemInfo()};
    emitFunctionPrologue(
        functionNode,
        Builder.createBasicBlock(outerFn),
        InitES5CaptureState::Yes,
        DoEmitParameters::No);

    
    auto *gen = Builder.createCreateGeneratorInst(innerFn);

    if (!hasSimpleParams(functionNode)) {
      
      
      Value *next = Builder.createLoadPropertyInst(gen, "STR");
      Builder.createCallInst(next, gen, {});
    }

    emitFunctionEpilogue(gen);
  }

  return outerFn;
}