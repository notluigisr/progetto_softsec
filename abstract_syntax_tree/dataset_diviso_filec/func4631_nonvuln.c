  Expression_Obj Parser::parse_space_list()
  {
    NESTING_GUARD(nestings);
    Expression_Obj disj1 = parse_disjunction();
    
    if (peek_css< space_list_terminator >(position)
    ) {
      return disj1; }

    List_Obj space_list = SASS_MEMORY_NEW(List, pstate, 2, SASS_SPACE);
    space_list->append(disj1);

    while (
      !(peek_css< space_list_terminator >(position)) &&
      peek_css< optional_css_whitespace >() != end
    ) {
      
      space_list->append(parse_disjunction());
    }
    
    return space_list;
  }