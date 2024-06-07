void HGraphBuilder::GenerateGetCachedArrayIndex(CallRuntime* call) {
  ASSERT(call->arguments()->length() == 1);
  CHECK_ALIVE(VisitForValue(call->arguments()->at(0)));
  HValue* value = Pop();
  HGetCachedArrayIndex* result = new(zone()) HGetCachedArrayIndex(value);
  return ast_context()->ReturnInstruction(result, call->id());
}