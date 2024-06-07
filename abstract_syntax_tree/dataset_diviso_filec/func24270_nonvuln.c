void HGraphBuilder::VisitForStatement(ForStatement* stmt) {
  ASSERT(!HasStackOverflow());
  ASSERT(current_block() != NULL);
  ASSERT(current_block()->HasPredecessor());
  if (stmt->init() != NULL) {
    CHECK_ALIVE(Visit(stmt->init()));
  }
  ASSERT(current_block() != NULL);
  bool osr_entry = PreProcessOsrEntry(stmt);
  HBasicBlock* loop_entry = CreateLoopHeaderBlock();
  current_block()->Goto(loop_entry);
  set_current_block(loop_entry);
  if (osr_entry) graph()->set_osr_loop_entry(loop_entry);

  HBasicBlock* loop_successor = NULL;
  if (stmt->cond() != NULL) {
    HBasicBlock* body_entry = graph()->CreateBasicBlock();
    loop_successor = graph()->CreateBasicBlock();
    CHECK_BAILOUT(VisitForControl(stmt->cond(), body_entry, loop_successor));
    if (body_entry->HasPredecessor()) {
      body_entry->SetJoinId(stmt->BodyId());
      set_current_block(body_entry);
    }
    if (loop_successor->HasPredecessor()) {
      loop_successor->SetJoinId(stmt->ExitId());
    } else {
      loop_successor = NULL;
    }
  }

  BreakAndContinueInfo break_info(stmt);
  if (current_block() != NULL) {
    CHECK_BAILOUT(VisitLoopBody(stmt, loop_entry, &break_info));
  }
  HBasicBlock* body_exit =
      JoinContinue(stmt, current_block(), break_info.continue_block());

  if (stmt->next() != NULL && body_exit != NULL) {
    set_current_block(body_exit);
    CHECK_BAILOUT(Visit(stmt->next()));
    body_exit = current_block();
  }

  HBasicBlock* loop_exit = CreateLoop(stmt,
                                      loop_entry,
                                      body_exit,
                                      loop_successor,
                                      break_info.break_block());
  set_current_block(loop_exit);
}