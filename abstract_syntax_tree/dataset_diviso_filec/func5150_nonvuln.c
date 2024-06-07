Item *Item_default_value::transform(THD *thd, Item_transformer transformer,
                                    uchar *args)
{
  DBUG_ASSERT(!thd->stmt_arena->is_stmt_prepare());
  DBUG_ASSERT(arg);

  Item *new_item= arg->transform(thd, transformer, args);
  if (!new_item)
    return 0;

  
  if (arg != new_item)
    thd->change_item_tree(&arg, new_item);
  return (this->*transformer)(thd, args);
}