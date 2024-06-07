void HGraphBuilder::GenerateMathTan(CallRuntime* call) {
  ASSERT_EQ(1, call->arguments()->length());
  CHECK_ALIVE(VisitArgumentList(call->arguments()));
  HValue* context = environment()->LookupContext();
  HCallStub* result =
      new(zone()) HCallStub(context, CodeStub::TranscendentalCache, 1);
  result->set_transcendental_type(TranscendentalCache::TAN);
  Drop(1);
  return ast_context()->ReturnInstruction(result, call->id());
}