const char *Field_iterator_table_ref::get_db_name()
{
  if (table_ref->view)
    return table_ref->view_db.str;
  else if (table_ref->is_natural_join)
    return natural_join_it.column_ref()->safe_db_name();

  
  DBUG_ASSERT(!cmp(&table_ref->db, &table_ref->table->s->db) ||
              (table_ref->schema_table &&
               is_infoschema_db(&table_ref->table->s->db)));

  return table_ref->db.str;
}