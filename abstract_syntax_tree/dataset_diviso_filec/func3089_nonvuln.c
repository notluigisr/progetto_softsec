bool Window_funcs_computation::setup(THD *thd,
                                     List<Item_window_func> *window_funcs,
                                     JOIN_TAB *tab)
{
  order_window_funcs_by_window_specs(window_funcs);

  SQL_SELECT *sel= NULL;
  
  if (tab->filesort && tab->filesort->select)
  {
    sel= tab->filesort->select;
    DBUG_ASSERT(!sel->quick);
  }

  Window_funcs_sort *srt;
  List_iterator<Item_window_func> iter(*window_funcs);
  while (iter.peek())
  {
    if (!(srt= new Window_funcs_sort()) ||
        srt->setup(thd, sel, iter, tab))
    {
      return true;
    }
    win_func_sorts.push_back(srt, thd->mem_root);
  }
  return false;
}