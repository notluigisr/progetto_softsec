static int restore_db_collation(FILE *sql_file,
                                const char *db_name,
                                const char *delimiter,
                                const char *db_cl_name)
{
  char quoted_db_buf[NAME_LEN * 2 + 3];
  char *quoted_db_name= quote_name(db_name, quoted_db_buf, FALSE);

  CHARSET_INFO *db_cl= get_charset_by_name(db_cl_name, MYF(0));

  if (!db_cl)
    return 1;

  fprintf(sql_file,
          "STR",
          (const char *) quoted_db_name,
          (const char *) db_cl->csname,
          (const char *) db_cl->name,
          (const char *) delimiter);

  return 0;
}