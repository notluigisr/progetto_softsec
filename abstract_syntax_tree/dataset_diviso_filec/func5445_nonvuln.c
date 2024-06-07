LEX::add_primary_to_query_expression_body_ext_parens(
                                                 SELECT_LEX_UNIT *unit,
                                                 SELECT_LEX *sel,
                                                 enum sub_select_type unit_type,
                                                 bool distinct)
{
  SELECT_LEX *sel1= unit->first_select();
  if (unit->first_select()->next_select())
  {
    sel1= wrap_unit_into_derived(unit);
    if (!sel1)
      return NULL;
    if (!create_unit(sel1))
      return NULL;
  }
  SELECT_LEX *sel2= sel;
  if (sel->master_unit() && sel->master_unit()->first_select()->next_select())
  {
    sel2= wrap_unit_into_derived(sel->master_unit());
    if (!sel2)
      return NULL;
  }
  unit= parsed_select_expr_start(sel1, sel2, unit_type, distinct);
  return unit;
}