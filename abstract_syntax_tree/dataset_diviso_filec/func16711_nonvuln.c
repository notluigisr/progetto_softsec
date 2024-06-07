record_merge_function_type (int merger, uniqstr type, location declaration_loc)
{
  if (merger <= 0)
    return;

  if (type == NULL)
    type = uniqstr_new ("");

  merger_list *merge_function;
  int merger_find = 1;
  for (merge_function = merge_functions;
       merge_function != NULL && merger_find != merger;
       merge_function = merge_function->next)
    merger_find += 1;
  aver (merge_function != NULL && merger_find == merger);
  if (merge_function->type != NULL && !UNIQSTR_EQ (merge_function->type, type))
    {
      complain (&declaration_loc, complaint,
                _("STR"
                "STR"),
                quote (merge_function->name), type,
                merge_function->type);
      subcomplain (&merge_function->type_declaration_loc, complaint,
                   _("STR"));
    }
  merge_function->type = uniqstr_new (type);
  merge_function->type_declaration_loc = declaration_loc;
}