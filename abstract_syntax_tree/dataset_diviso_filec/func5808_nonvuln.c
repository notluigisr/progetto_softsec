  Selector_List_Obj Parser::parse_selector(const char* beg, Context& ctx, Backtraces traces, ParserState pstate, const char* source, bool allow_parent)
  {
    Parser p = Parser::from_c_str(beg, ctx, traces, pstate, source, allow_parent);
    
    return p.parse_selector_list(false);
  }