parser_pop_block_context (parser_context_t *context_p) 
{
  JERRY_ASSERT (context_p->stack_top_uint8 == PARSER_STATEMENT_BLOCK_SCOPE
                || context_p->stack_top_uint8 == PARSER_STATEMENT_PRIVATE_SCOPE
                || context_p->stack_top_uint8 == PARSER_STATEMENT_BLOCK_CONTEXT
                || context_p->stack_top_uint8 == PARSER_STATEMENT_PRIVATE_CONTEXT);

  uint8_t type = context_p->stack_top_uint8;

  parser_block_statement_t block_statement;

  parser_stack_pop_uint8 (context_p);
  parser_stack_pop (context_p, &block_statement, sizeof (parser_block_statement_t));

  context_p->scope_stack_top = block_statement.scope_stack_top;
  context_p->scope_stack_reg_top = block_statement.scope_stack_reg_top;

  if (type == PARSER_STATEMENT_BLOCK_CONTEXT || type == PARSER_STATEMENT_PRIVATE_CONTEXT)
  {
    PARSER_MINUS_EQUAL_U16 (context_p->stack_depth, PARSER_BLOCK_CONTEXT_STACK_ALLOCATION);
#ifndef JERRY_NDEBUG
    PARSER_MINUS_EQUAL_U16 (context_p->context_stack_depth, PARSER_BLOCK_CONTEXT_STACK_ALLOCATION);
#endif 

    parser_block_context_t block_context;
    parser_stack_pop (context_p, &block_context, sizeof (parser_block_context_t));

    parser_emit_cbc (context_p, CBC_CONTEXT_END);
    parser_set_branch_to_current_position (context_p, &block_context.branch);
  }

  parser_stack_iterator_init (context_p, &context_p->last_statement);
} 