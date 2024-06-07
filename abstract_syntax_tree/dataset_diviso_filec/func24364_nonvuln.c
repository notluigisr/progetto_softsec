Item* Item_ref::transform(THD *thd, Item_transformer transformer, uchar *arg)
{
  DBUG_ASSERT(!thd->stmt_arena->is_stmt_prepare());
  DBUG_ASSERT((*ref) != NULL);

  
  Item *new_item= (*ref)->transform(thd, transformer, arg);
  if (!new_item)
    return NULL;

  
  if (*ref != new_item)
    thd->change_item_tree(ref, new_item);

  
  return (this->*transformer)(thd, arg);
}