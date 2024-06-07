void HGlobalValueNumberer::ProcessLoopBlock(
    HBasicBlock* block,
    HBasicBlock* loop_header,
    GVNFlagSet loop_kills,
    GVNFlagSet* first_time_depends,
    GVNFlagSet* first_time_changes) {
  HBasicBlock* pre_header = loop_header->predecessors()->at(0);
  GVNFlagSet depends_flags = HValue::ConvertChangesToDependsFlags(loop_kills);
  TRACE_GVN_2("STR",
              block->block_id(),
              *GetGVNFlagsString(depends_flags));
  HInstruction* instr = block->first();
  while (instr != NULL) {
    HInstruction* next = instr->next();
    bool hoisted = false;
    if (instr->CheckFlag(HValue::kUseGVN)) {
      TRACE_GVN_4("STR",
                  instr->id(),
                  instr->Mnemonic(),
                  *GetGVNFlagsString(instr->gvn_flags()),
                  *GetGVNFlagsString(loop_kills));
      bool can_hoist = !instr->gvn_flags().ContainsAnyOf(depends_flags);
      if (can_hoist && !graph()->use_optimistic_licm()) {
        can_hoist = block->IsLoopSuccessorDominator();
      }

      if (can_hoist) {
        bool inputs_loop_invariant = true;
        for (int i = 0; i < instr->OperandCount(); ++i) {
          if (instr->OperandAt(i)->IsDefinedAfter(pre_header)) {
            inputs_loop_invariant = false;
          }
        }

        if (inputs_loop_invariant && ShouldMove(instr, loop_header)) {
          TRACE_GVN_1("STR", instr->id());
          
          instr->Unlink();
          instr->InsertBefore(pre_header->end());
          if (instr->HasSideEffects()) removed_side_effects_ = true;
          hoisted = true;
        }
      }
    }
    if (!hoisted) {
      
      
      GVNFlagSet previous_depends = *first_time_depends;
      GVNFlagSet previous_changes = *first_time_changes;
      first_time_depends->Add(instr->DependsOnFlags());
      first_time_changes->Add(instr->ChangesFlags());
      if (!(previous_depends == *first_time_depends)) {
        TRACE_GVN_1("STR",
                    *GetGVNFlagsString(*first_time_depends));
      }
      if (!(previous_changes == *first_time_changes)) {
        TRACE_GVN_1("STR",
                    *GetGVNFlagsString(*first_time_changes));
      }
    }
    instr = next;
  }
}