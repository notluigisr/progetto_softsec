static void clear_field_flag(TABLE *table)
{
  Field **ptr;
  DBUG_ENTER("STR");

  for (ptr= table->field; *ptr; ptr++)
    (*ptr)->flags&= (~GET_FIXED_FIELDS_FLAG);
  DBUG_VOID_RETURN;
}