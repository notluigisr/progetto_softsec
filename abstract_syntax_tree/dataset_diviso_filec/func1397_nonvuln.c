  Expression_Obj Parser::parse_relation()
  {
    NESTING_GUARD(nestings);
    advanceToNextToken();
    ParserState state(pstate);
    
    Expression_Obj lhs = parse_expression();
    std::vector<Expression_Obj> operands;
    std::vector<Operand> operators;
    
    while (peek< alternatives <
            kwd_eq,
            kwd_neq,
            kwd_gte,
            kwd_gt,
            kwd_lte,
            kwd_lt
          > >(position))
    {
      
      bool left_ws = peek < css_comments >() != NULL;
      
      enum Sass_OP op
      = lex<kwd_eq>()  ? Sass_OP::EQ
      : lex<kwd_neq>() ? Sass_OP::NEQ
      : lex<kwd_gte>() ? Sass_OP::GTE
      : lex<kwd_lte>() ? Sass_OP::LTE
      : lex<kwd_gt>()  ? Sass_OP::GT
      : lex<kwd_lt>()  ? Sass_OP::LT
      
      :                  Sass_OP::EQ;
      
      bool right_ws = peek < css_comments >() != NULL;
      operators.push_back({ op, left_ws, right_ws });
      operands.push_back(parse_expression());
    }
    
    
    
    
    
    Expression_Obj ex = fold_operands(lhs, operands, operators);
    state.offset = pstate - state + pstate.offset;
    ex->pstate(state);
    return ex;
  }