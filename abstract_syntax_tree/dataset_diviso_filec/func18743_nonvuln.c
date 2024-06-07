  Supports_Block_Obj Parser::parse_supports_directive()
  {
    Supports_Condition_Obj cond = parse_supports_condition();
    if (!cond) {
      css_error("STR", false);
    }
    
    Supports_Block_Obj query = SASS_MEMORY_NEW(Supports_Block, pstate, cond);
    
    
    query->block(parse_block());
    
    return query;
  }