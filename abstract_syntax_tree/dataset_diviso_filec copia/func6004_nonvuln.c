parser_pattern_get_target (parser_context_t *context_p, 
                           parser_pattern_flags_t flags) 
{
  parser_pattern_end_marker_t end_marker;
  end_marker.token.type = LEXER_INVALID_PATTERN;
  parser_branch_t skip_init;

  if (flags & PARSER_PATTERN_TARGET_DEFAULT)
  {
    JERRY_ASSERT (flags & PARSER_PATTERN_TARGET_ON_STACK);

    parser_emit_cbc_ext_forward_branch (context_p, CBC_EXT_DEFAULT_INITIALIZER, &skip_init);
  }

  if ((flags & (PARSER_PATTERN_TARGET_ON_STACK | PARSER_PATTERN_TARGET_DEFAULT)) != PARSER_PATTERN_TARGET_ON_STACK)
  {
    scanner_location_t start_location;

    if (context_p->next_scanner_info_p->source_p != context_p->source_p
        || context_p->next_scanner_info_p->type == SCANNER_TYPE_ERR_REDECLARED
        || (flags & PARSER_PATTERN_REST_ELEMENT))
    {
      
      parser_emit_cbc (context_p, CBC_PUSH_NULL);
    }
    else
    {
      JERRY_ASSERT (context_p->next_scanner_info_p->type == SCANNER_TYPE_INITIALIZER);
      scanner_get_location (&start_location, context_p);

      scanner_set_location (context_p, &((scanner_location_info_t *) context_p->next_scanner_info_p)->location);
      scanner_release_next (context_p, sizeof (scanner_location_info_t));
      scanner_seek (context_p);
      lexer_next_token (context_p);

      parser_parse_expression (context_p, PARSE_EXPR_NO_COMMA);
      scanner_get_location (&(end_marker.location), context_p);
      end_marker.token = context_p->token;

      scanner_set_location (context_p, &start_location);
      scanner_seek (context_p);
      parser_flush_cbc (context_p);
    }
  }

  if (flags & PARSER_PATTERN_TARGET_DEFAULT)
  {
    parser_set_branch_to_current_position (context_p, &skip_init);
  }

  return end_marker;
} 