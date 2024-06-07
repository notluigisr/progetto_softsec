lexer_string_is_use_strict (parser_context_t *context_p) 
{
  JERRY_ASSERT (context_p->token.type == LEXER_LITERAL
                && context_p->token.lit_location.type == LEXER_STRING_LITERAL);

  return (context_p->token.lit_location.length == 10
          && !context_p->token.lit_location.has_escape
          && memcmp (context_p->token.lit_location.char_p, "STR", 10) == 0);
} 