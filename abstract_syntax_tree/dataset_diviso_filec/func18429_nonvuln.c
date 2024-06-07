bool Item_in_subselect::fix_fields(THD *thd_arg, Item **ref)
{
  uint outer_cols_num;
  List<Item> *inner_cols;
  char const *save_where= thd_arg->where;
  DBUG_ENTER("STR");

  thd= thd_arg;
  DBUG_ASSERT(unit->thd == thd);

  if (test_strategy(SUBS_SEMI_JOIN))
    DBUG_RETURN( !( (*ref)= new (thd->mem_root) Item_int(thd, 1)) );

  thd->where= "STR";
  
  if (engine &&
      engine->engine_type() == subselect_engine::SINGLE_SELECT_ENGINE &&
      ((subselect_single_select_engine*)engine)->join)
  {
    outer_cols_num= left_expr->cols();

    if (unit->is_union())
      inner_cols= &(unit->types);
    else
      inner_cols= &(unit->first_select()->item_list);
    if (outer_cols_num != inner_cols->elements)
    {
      my_error(ER_OPERAND_COLUMNS, MYF(0), outer_cols_num);
      goto err;
    }
    if (outer_cols_num > 1)
    {
      List_iterator<Item> inner_col_it(*inner_cols);
      Item *inner_col;
      for (uint i= 0; i < outer_cols_num; i++)
      {
        inner_col= inner_col_it++;
        if (inner_col->check_cols(left_expr->element_index(i)->cols()))
          goto err;
      }
    }
  }

  if (left_expr && !left_expr->fixed &&
      left_expr->fix_fields(thd_arg, &left_expr))
    goto err;
  else
  if (Item_subselect::fix_fields(thd_arg, ref))
    goto err;
  fixed= TRUE;
  thd->where= save_where;
  DBUG_RETURN(FALSE);

err:
  thd->where= save_where;
  DBUG_RETURN(TRUE);
}