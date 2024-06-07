Item *LEX::create_item_func_lastval(THD *thd, Table_ident *table_ident)
{
  TABLE_LIST *table;
  if (unlikely(!(table= current_select->add_table_to_list(thd, table_ident, 0,
                                                          TL_OPTION_SEQUENCE,
                                                          TL_READ,
                                                          MDL_SHARED_READ))))
    return NULL;
  thd->lex->set_stmt_unsafe(LEX::BINLOG_STMT_UNSAFE_SYSTEM_FUNCTION);
  return new (thd->mem_root) Item_func_lastval(thd, table);
}