void HGraphBuilder::AddPhi(HPhi* instr) {
  ASSERT(current_block() != NULL);
  current_block()->AddPhi(instr);
}