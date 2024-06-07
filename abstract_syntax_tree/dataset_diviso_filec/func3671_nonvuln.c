const char *Field_iterator_table_ref::get_table_name()
{
  if (table_ref->view)
    return table_ref->view_name.str;
  if (table_ref->is_derived())
    return table_ref->table->s->table_name.str;
  else if (table_ref->is_natural_join)
    return natural_join_it.column_ref()->table_name();

  DBUG_ASSERT(!strcmp(table_ref->table_name,
                      table_ref->table->s->table_name.str) ||
              table_ref->schema_table);
  return table_ref->table_name;
}