static void trace_stop(jit_State *J)
{
  BCIns *pc = mref(J->cur.startpc, BCIns);
  BCOp op = bc_op(J->cur.startins);
  GCproto *pt = &gcref(J->cur.startpt)->pt;
  TraceNo traceno = J->cur.traceno;
  GCtrace *T = trace_save_alloc(J);  
  lua_State *L;

  switch (op) {
  case BC_FORL:
    setbc_op(pc+bc_j(J->cur.startins), BC_JFORI);  
    
  case BC_LOOP:
  case BC_ITERL:
  case BC_FUNCF:
    
    setbc_op(pc, (int)op+(int)BC_JLOOP-(int)BC_LOOP);
    setbc_d(pc, traceno);
  addroot:
    
    J->cur.nextroot = pt->trace;
    pt->trace = (TraceNo1)traceno;
    break;
  case BC_RET:
  case BC_RET0:
  case BC_RET1:
    *pc = BCINS_AD(BC_JLOOP, J->cur.snap[0].nslots, traceno);
    goto addroot;
  case BC_JMP:
    
    lua_assert(J->parent != 0 && J->cur.root != 0);
    lj_asm_patchexit(J, traceref(J, J->parent), J->exitno, J->cur.mcode);
    
    traceref(J, J->parent)->snap[J->exitno].count = SNAPCOUNT_DONE;
    
    {
      GCtrace *root = traceref(J, J->cur.root);
      root->nchild++;
      J->cur.nextside = root->nextside;
      root->nextside = (TraceNo1)traceno;
    }
    break;
  default:
    lua_assert(0);
    break;
  }

  
  lj_mcode_commit(J, J->cur.mcode);
  J->postproc = LJ_POST_NONE;
  trace_save(J, T);

  L = J->L;
  lj_vmevent_send(L, TRACE,
    setstrV(L, L->top++, lj_str_newlit(L, "STR"));
    setintV(L->top++, traceno);
  );
}