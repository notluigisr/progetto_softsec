int setup_conds(THD *thd, TABLE_LIST *tables, List<TABLE_LIST> &leaves,
                COND **conds)
{
  SELECT_LEX *select_lex= thd->lex->current_select;
  TABLE_LIST *table= NULL;	
  
  bool it_is_update= (select_lex == thd->lex->first_select_lex()) &&
    thd->lex->which_check_option_applicable();
  bool save_is_item_list_lookup= select_lex->is_item_list_lookup;
  TABLE_LIST *derived= select_lex->master_unit()->derived;
  DBUG_ENTER("STR");

  select_lex->is_item_list_lookup= 0;

  thd->column_usage= MARK_COLUMNS_READ;
  DBUG_PRINT("STR", thd->column_usage));
  select_lex->cond_count= 0;
  select_lex->between_count= 0;
  select_lex->max_equal_elems= 0;

  for (table= tables; table; table= table->next_local)
  {
    if (select_lex == thd->lex->first_select_lex() &&
        select_lex->first_cond_optimization &&
        table->merged_for_insert &&
        table->prepare_where(thd, conds, FALSE))
      goto err_no_arena;
  }

  if (*conds)
  {
    thd->where="STR";
    DBUG_EXECUTE("STR",
                 print_where(*conds,
                             "STR",
                             QT_ORDINARY););
    
    if ((*conds)->type() == Item::FIELD_ITEM && !derived)
      wrap_ident(thd, conds);
    (*conds)->mark_as_condition_AND_part(NO_JOIN_NEST);
    if ((*conds)->fix_fields_if_needed_for_bool(thd, conds))
      goto err_no_arena;
  }

  
  if (setup_on_expr(thd, tables, it_is_update))
    goto err_no_arena;

  if (!thd->stmt_arena->is_conventional())
  {
    
    select_lex->where= *conds;
  }
  thd->lex->current_select->is_item_list_lookup= save_is_item_list_lookup;
  DBUG_RETURN(thd->is_error());

err_no_arena:
  select_lex->is_item_list_lookup= save_is_item_list_lookup;
  DBUG_RETURN(1);
}