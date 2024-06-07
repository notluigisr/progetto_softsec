void Item_allany_subselect::cleanup()
{
  
  for (SELECT_LEX *sl= unit->first_select();
       sl; sl= sl->next_select())
    if (test_set_strategy(SUBS_MAXMIN_INJECTED))
      sl->with_sum_func= false;
  Item_in_subselect::cleanup();
}