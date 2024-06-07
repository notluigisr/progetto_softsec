void HGraphBuilder::VisitTypeof(UnaryOperation* expr) {
  CHECK_ALIVE(VisitForTypeOf(expr->expression()));
  HValue* value = Pop();
  HValue* context = environment()->LookupContext();
  HInstruction* instr = new(zone()) HTypeof(context, value);
  return ast_context()->ReturnInstruction(instr, expr->id());
}