bool LEX::sp_proc_stmt_statement_finalize(THD *thd, bool no_lookahead)
{
  
  Lex_input_stream *lip= &thd->m_parser_state->m_lip;
  Lex_cstring qbuf(sphead->m_tmp_query, no_lookahead ? lip->get_ptr() :
                                                       lip->get_tok_start());
  return LEX::sp_proc_stmt_statement_finalize_buf(thd, qbuf);
}