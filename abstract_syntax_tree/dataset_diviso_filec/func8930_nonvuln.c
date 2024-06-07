static bool mark_as_dependent(THD *thd, SELECT_LEX *last, SELECT_LEX *current,
                              Item_ident *resolved_item,
                              Item_ident *mark_item,
                              bool suppress_warning_output)
{
  DBUG_ENTER("STR");
  DBUG_PRINT("STR",
                      current->select_number, current,
                      (last ? last->select_number : 0), last));

  
  if (mark_item && mark_item->can_be_depended)
  {
    DBUG_PRINT("STR", mark_item, last));
    mark_item->depended_from= last;
  }
  if (current->mark_as_dependent(thd, last,
                                  mark_item))
    DBUG_RETURN(TRUE);
  if ((thd->lex->describe & DESCRIBE_EXTENDED) && !suppress_warning_output)
  {
    const char *db_name= (resolved_item->db_name ?
                          resolved_item->db_name : "");
    const char *table_name= (resolved_item->table_name ?
                             resolved_item->table_name : "");
    push_warning_printf(thd, Sql_condition::WARN_LEVEL_NOTE,
                        ER_WARN_FIELD_RESOLVED,
                        ER_THD(thd,ER_WARN_FIELD_RESOLVED),
                        db_name, (db_name[0] ? "STR"),
                        table_name, (table_name [0] ? "STR"),
                        resolved_item->field_name,
                        current->select_number, last->select_number);
  }
  DBUG_RETURN(FALSE);
}