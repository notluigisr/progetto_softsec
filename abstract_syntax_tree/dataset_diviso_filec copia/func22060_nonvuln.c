  bool sp_for_loop_finalize(THD *thd, const Lex_for_loop_st &loop)
  {
    return loop.is_for_loop_cursor() ?
           sp_for_loop_cursor_finalize(thd, loop) :
           sp_for_loop_intrange_finalize(thd, loop);
  }