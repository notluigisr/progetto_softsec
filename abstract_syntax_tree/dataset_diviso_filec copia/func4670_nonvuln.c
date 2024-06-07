parser_check_left_hand_side_expression (parser_context_t *context_p, 
                                        uint16_t opcode) 
{
  if (opcode == CBC_PUSH_LITERAL
      && context_p->last_cbc.literal_type == LEXER_IDENT_LITERAL)
  {
    context_p->last_cbc_opcode = PARSER_CBC_UNAVAILABLE;
    return CBC_ASSIGN_SET_IDENT;
  }
  else if (opcode == CBC_PUSH_PROP)
  {
    context_p->last_cbc_opcode = PARSER_CBC_UNAVAILABLE;
    return CBC_ASSIGN;
  }
  else if (opcode == CBC_PUSH_PROP_LITERAL)
  {
    context_p->last_cbc_opcode = PARSER_CBC_UNAVAILABLE;
    return CBC_ASSIGN_PROP_LITERAL;
  }
  else if (opcode == CBC_PUSH_PROP_LITERAL_LITERAL)
  {
    context_p->last_cbc_opcode = CBC_PUSH_TWO_LITERALS;
    return CBC_ASSIGN;
  }
  else if (opcode == CBC_PUSH_PROP_THIS_LITERAL)
  {
    context_p->last_cbc_opcode = CBC_PUSH_THIS_LITERAL;
    return CBC_ASSIGN;
  }
  else
  {
    
#if JERRY_ESNEXT
    parser_raise_error (context_p, PARSER_ERR_INVALID_LHS_FOR_LOOP);
#else 
    parser_emit_cbc_ext (context_p, CBC_EXT_THROW_REFERENCE_ERROR);
#endif 

    return CBC_ASSIGN;
  }

  return opcode;
} 