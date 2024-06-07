bool TABLE_LIST::setup_underlying(THD *thd)
{
  DBUG_ENTER("STR");

  if (!view || (!field_translation && merge_underlying_list))
  {
    SELECT_LEX *select= get_single_select();

    if (create_field_translation(thd))
      DBUG_RETURN(TRUE);

    
    if (select->ftfunc_list->elements)
    {
      Item_func_match *ifm;
      SELECT_LEX *current_select= thd->lex->current_select;
      List_iterator_fast<Item_func_match>
        li(*(select_lex->ftfunc_list));
      while ((ifm= li++))
        current_select->ftfunc_list->push_front(ifm);
    }
  }
  DBUG_RETURN(FALSE);
}