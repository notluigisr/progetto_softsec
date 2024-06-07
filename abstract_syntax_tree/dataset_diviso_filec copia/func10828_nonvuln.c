lexer_check_yield_no_arg (parser_context_t *context_p) 
{
  if (context_p->token.flags & LEXER_WAS_NEWLINE)
  {
    return true;
  }

  switch (context_p->token.type)
  {
    case LEXER_RIGHT_BRACE:
    case LEXER_RIGHT_PAREN:
    case LEXER_RIGHT_SQUARE:
    case LEXER_COMMA:
    case LEXER_COLON:
    case LEXER_SEMICOLON:
    case LEXER_EOS:
    {
      return true;
    }
    default:
    {
      return false;
    }
  }
} 