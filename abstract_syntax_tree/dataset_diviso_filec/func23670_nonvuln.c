Item *Item_field::derived_field_transformer_for_where(THD *thd, uchar *arg)
{
  st_select_lex *sel= (st_select_lex *)arg;
  Item *producing_item= find_producing_item(this, sel);
  if (producing_item)
  {
    Item *producing_clone= producing_item->build_clone(thd);
    if (producing_clone)
      producing_clone->marker|= SUBSTITUTION_FL;
    return producing_clone;
  }
  return this;
}