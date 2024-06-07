void ESTreeIRGen::emitFunctionEpilogue(Value *returnValue) {
  if (returnValue) {
    Builder.setLocation(SourceErrorManager::convertEndToLocation(
        Builder.getFunction()->getSourceRange()));
    Builder.createReturnInst(returnValue);
  }

  
  if (!curFunction()->createArgumentsInst->hasUsers())
    curFunction()->createArgumentsInst->eraseFromParent();

  curFunction()->function->clearStatementCount();
}