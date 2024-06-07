Item *Field_num::get_equal_zerofill_const_item(THD *thd, const Context &ctx,
                                               Item *const_item)
{
  switch (ctx.subst_constraint()) {
  case IDENTITY_SUBST:
    return NULL; 
  case ANY_SUBST:
    break;
  }
  DBUG_ASSERT(const_item->const_item());
  DBUG_ASSERT(ctx.compare_type() != STRING_RESULT);
  return const_item;
}