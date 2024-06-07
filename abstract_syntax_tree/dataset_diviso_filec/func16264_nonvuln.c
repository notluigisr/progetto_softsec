compile_tree_empty_check(Node* node, regex_t* reg, int empty_info, ScanEnv* env)
{
  int r;
  int saved_num_null_check = reg->num_null_check;

  if (empty_info != BODY_IS_NOT_EMPTY) {
    r = add_op(reg, OP_EMPTY_CHECK_START);
    if (r != 0) return r;
    COP(reg)->empty_check_start.mem = reg->num_null_check; 
    reg->num_null_check++;
  }

  r = compile_tree(node, reg, env);
  if (r != 0) return r;

  if (empty_info != BODY_IS_NOT_EMPTY) {
    if (empty_info == BODY_IS_EMPTY)
      r = add_op(reg, OP_EMPTY_CHECK_END);
    else if (empty_info == BODY_IS_EMPTY_MEM)
      r = add_op(reg, OP_EMPTY_CHECK_END_MEMST);
    else if (empty_info == BODY_IS_EMPTY_REC)
      r = add_op(reg, OP_EMPTY_CHECK_END_MEMST_PUSH);

    if (r != 0) return r;
    COP(reg)->empty_check_end.mem = saved_num_null_check; 
  }
  return r;
}