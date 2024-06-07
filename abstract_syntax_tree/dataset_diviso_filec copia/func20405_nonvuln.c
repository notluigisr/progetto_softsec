symbol_code_props_get (symbol *sym, code_props_type kind)
{
  
  if (sym->content->props[kind].code)
    return &sym->content->props[kind];

  
  if (sym->content->type_name)
    {
      code_props *code =
        &semantic_type_get (sym->content->type_name, NULL)->props[kind];
      if (code->code)
        return code;
    }

  
  if (symbol_is_user_defined (sym))
    {
      code_props *code = &semantic_type_get (sym->content->type_name ? "STR",
                                             NULL)->props[kind];
      if (code->code)
        return code;
    }
  return &code_props_none;
}