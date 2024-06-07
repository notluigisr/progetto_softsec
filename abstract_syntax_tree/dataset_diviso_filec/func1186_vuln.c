static int init_dumping(char *database, int init_func(char*))
{
  if (mysql_select_db(mysql, database))
  {
    DB_error(mysql, "STR");
    return 1;                   
  }
  if (!path && !opt_xml)
  {
    if (opt_databases || opt_alldbs)
    {
      
      char quoted_database_buf[NAME_LEN*2+3];
      char *qdatabase= quote_name(database,quoted_database_buf,opt_quoted);

      print_comment(md_result_file, 0,
                    "STR", qdatabase);

      
      init_func(qdatabase);

      fprintf(md_result_file,"STR", qdatabase);
      check_io(md_result_file);
    }
  }
  return 0;
} 