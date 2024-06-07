bool Field::can_optimize_keypart_ref(const Item_bool_func *cond,
                                     const Item *item) const
{
  DBUG_ASSERT(cmp_type() != STRING_RESULT);
  DBUG_ASSERT(cmp_type() != TIME_RESULT);
  return item->cmp_type() != TIME_RESULT;
}