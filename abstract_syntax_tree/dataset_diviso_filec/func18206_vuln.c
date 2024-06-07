bool Item::cache_const_expr_analyzer(uchar **arg)
{
  bool *cache_flag= (bool*)*arg;
  if (!*cache_flag)
  {
    Item *item= real_item();
    
    if (const_item() &&
        !(basic_const_item() || item->basic_const_item() ||
          item->type() == Item::FIELD_ITEM ||
          item->type() == SUBSELECT_ITEM ||
           
          (item->type() == Item::FUNC_ITEM &&
           ((Item_func*)item)->functype() == Item_func::GUSERVAR_FUNC)))
      *cache_flag= TRUE;
    return TRUE;
  }
  return FALSE;
}