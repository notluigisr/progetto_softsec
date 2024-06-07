Item *Item_func_le::negated_item(THD *thd) 
{
  return new (thd->mem_root) Item_func_gt(thd, args[0], args[1]);
}