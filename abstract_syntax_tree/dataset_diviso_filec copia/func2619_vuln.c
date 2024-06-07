int setup_order(THD *thd, Ref_ptr_array ref_pointer_array, TABLE_LIST *tables,
                List<Item> &fields, List<Item> &all_fields, ORDER *order,
                bool from_window_spec)
{ 
  SELECT_LEX *select = thd->lex->current_select;
  enum_parsing_place context_analysis_place=
                     thd->lex->current_select->context_analysis_place;
  thd->where="STR";
  const bool for_union = select->master_unit()->is_union() &&
                         select == select->master_unit()->fake_select_lex;
  for (uint number = 1; order; order=order->next, number++)
  {
    if (find_order_in_list(thd, ref_pointer_array, tables, order, fields,
                           all_fields, false, true, from_window_spec))
      return 1;
    if ((*order->item)->with_window_func &&
        context_analysis_place != IN_ORDER_BY)
    {
      my_error(ER_WINDOW_FUNCTION_IN_WINDOW_SPEC, MYF(0));
      return 1;
    }

    

    if (for_union && (*order->item)->with_sum_func)
    {
      my_error(ER_AGGREGATE_ORDER_FOR_UNION, MYF(0), number);
      return 1;
    }

    if (from_window_spec && (*order->item)->with_sum_func &&
        (*order->item)->type() != Item::SUM_FUNC_ITEM)
      (*order->item)->split_sum_func(thd, ref_pointer_array,
                                     all_fields, SPLIT_SUM_SELECT);
  }
  return 0;
}