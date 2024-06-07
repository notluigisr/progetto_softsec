parser_validate_lexical_context (parser_context_t *context_p) 
{
  JERRY_ASSERT (context_p->token.type == LEXER_KEYW_LET
                || context_p->token.type == LEXER_KEYW_CONST
                || context_p->token.type == LEXER_KEYW_CLASS);

  if (parser_statement_flags[context_p->stack_top_uint8] & PARSER_STATM_SINGLE_STATM)
  {
    parser_raise_error (context_p, PARSER_ERR_LEXICAL_SINGLE_STATEMENT);
  }
} 