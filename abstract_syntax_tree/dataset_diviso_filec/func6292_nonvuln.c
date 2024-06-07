init_lex_with_single_table(THD *thd, TABLE *table, LEX *lex)
{
  TABLE_LIST *table_list;
  Table_ident *table_ident;
  SELECT_LEX *select_lex= &lex->select_lex;
  Name_resolution_context *context= &select_lex->context;
  
  thd->lex= lex;
  lex_start(thd);
  context->init();
  if ((!(table_ident= new Table_ident(thd,
                                      table->s->table_name,
                                      table->s->db, TRUE))) ||
      (!(table_list= select_lex->add_table_to_list(thd,
                                                   table_ident,
                                                   NULL,
                                                   0))))
    return TRUE;
  context->resolve_in_table_list_only(table_list);
  lex->use_only_table_context= TRUE;
  select_lex->cur_pos_in_select_list= UNDEF_POS;
  table->map= 1; 
  table->get_fields_in_item_tree= TRUE;
  table_list->table= table;
  table_list->cacheable_table= false;
  return FALSE;
}