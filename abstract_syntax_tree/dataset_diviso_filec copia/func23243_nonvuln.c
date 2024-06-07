print_table_data_html(MYSQL_RES *result)
{
  MYSQL_ROW	cur;
  MYSQL_FIELD	*field;

  mysql_field_seek(result,0);
  (void) tee_fputs("STR", PAGER);
  if (column_names)
  {
    while((field = mysql_fetch_field(result)))
    {
      tee_fputs("STR", PAGER);
      if (field->name && field->name[0])
        xmlencode_print(field->name, field->name_length);
      else
        tee_fputs(field->name ? "STR", PAGER);
      tee_fputs("STR", PAGER);
    }
    (void) tee_fputs("STR", PAGER);
  }
  while ((cur = mysql_fetch_row(result)))
  {
    if (interrupted_query)
      break;
    ulong *lengths=mysql_fetch_lengths(result);
    field= mysql_fetch_fields(result);
    (void) tee_fputs("STR", PAGER);
    for (uint i=0; i < mysql_num_fields(result); i++)
    {
      (void) tee_fputs("STR", PAGER);
      if (opt_binhex && is_binary_field(&field[i]))
        print_as_hex(PAGER, cur[i], lengths[i], lengths[i]);
      else
        xmlencode_print(cur[i], lengths[i]);
      (void) tee_fputs("STR", PAGER);
    }
    (void) tee_fputs("STR", PAGER);
  }
  (void) tee_fputs("STR", PAGER);
}