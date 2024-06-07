void HGraphBuilder::VisitThrow(Throw* expr) {
  ASSERT(!HasStackOverflow());
  ASSERT(current_block() != NULL);
  ASSERT(current_block()->HasPredecessor());
  
  
  
  ASSERT(ast_context()->IsEffect());
  CHECK_ALIVE(VisitForValue(expr->exception()));

  HValue* context = environment()->LookupContext();
  HValue* value = environment()->Pop();
  HThrow* instr = new(zone()) HThrow(context, value);
  instr->set_position(expr->position());
  AddInstruction(instr);
  AddSimulate(expr->id());
  current_block()->FinishExit(new(zone()) HAbnormalExit);
  set_current_block(NULL);
}