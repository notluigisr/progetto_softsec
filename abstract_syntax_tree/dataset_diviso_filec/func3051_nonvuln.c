void HGraph::DeadCodeElimination() {
  HPhase phase("STR", this);
  ZoneList<HInstruction*> worklist(blocks_.length(), zone());
  for (int i = 0; i < blocks()->length(); ++i) {
    for (HInstruction* instr = blocks()->at(i)->first();
         instr != NULL;
         instr = instr->next()) {
      if (instr->IsDead()) worklist.Add(instr, zone());
    }
  }

  while (!worklist.is_empty()) {
    HInstruction* instr = worklist.RemoveLast();
    if (FLAG_trace_dead_code_elimination) {
      HeapStringAllocator allocator;
      StringStream stream(&allocator);
      instr->PrintNameTo(&stream);
      stream.Add("STR");
      instr->PrintTo(&stream);
      PrintF("STR", *stream.ToCString());
    }
    instr->DeleteAndReplaceWith(NULL);
    for (int i = 0; i < instr->OperandCount(); ++i) {
      HValue* operand = instr->OperandAt(i);
      if (operand->IsDead()) worklist.Add(HInstruction::cast(operand), zone());
    }
  }
}