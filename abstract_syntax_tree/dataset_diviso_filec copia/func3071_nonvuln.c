semantic_type_code_props_set (semantic_type *type,
                              code_props_type kind,
                              code_props const *code)
{
  if (type->props[kind].code)
    complain_semantic_type_redeclared (type, code_props_type_string (kind),
                                       type->props[kind].location,
                                       code->location);
  else
    type->props[kind] = *code;
}