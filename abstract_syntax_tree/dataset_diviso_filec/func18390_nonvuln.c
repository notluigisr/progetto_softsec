  bool sp_for_loop_declarations(THD *thd, Lex_for_loop_st *loop,
                                const LEX_CSTRING *index,
                                const Lex_for_loop_bounds_st &bounds)
  {
    return bounds.is_for_loop_cursor() ?
           sp_for_loop_cursor_declarations(thd, loop, index, bounds) :
           sp_for_loop_intrange_declarations(thd, loop, index, bounds);
  }