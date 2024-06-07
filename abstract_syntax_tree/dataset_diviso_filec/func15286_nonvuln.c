bool multi_delete_set_locks_and_link_aux_tables(LEX *lex)
{
  TABLE_LIST *tables= lex->select_lex.table_list.first;
  TABLE_LIST *target_tbl;
  DBUG_ENTER("STR");

  lex->table_count= 0;

  for (target_tbl= lex->auxiliary_table_list.first;
       target_tbl; target_tbl= target_tbl->next_local)
  {
    lex->table_count++;
    
    TABLE_LIST *walk= multi_delete_table_match(lex, target_tbl, tables);
    if (!walk)
      DBUG_RETURN(TRUE);
    if (!walk->derived)
    {
      target_tbl->table_name= walk->table_name;
      target_tbl->table_name_length= walk->table_name_length;
    }
    walk->updating= target_tbl->updating;
    walk->lock_type= target_tbl->lock_type;
    
    DBUG_ASSERT(walk->lock_type >= TL_WRITE_ALLOW_WRITE);
    walk->mdl_request.set_type(MDL_SHARED_WRITE);
    target_tbl->correspondent_table= walk;	
  }
  DBUG_RETURN(FALSE);
}