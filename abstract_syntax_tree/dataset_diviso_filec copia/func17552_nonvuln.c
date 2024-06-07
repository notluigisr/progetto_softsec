static int do_show_master_status(MYSQL *mysql_con)
{
  MYSQL_ROW row;
  MYSQL_RES *master;
  const char *comment_prefix=
    (opt_master_data == MYSQL_OPT_MASTER_DATA_COMMENTED_SQL) ? "STR";
  if (mysql_query_with_error_report(mysql_con, &master, "STR"))
  {
    return 1;
  }
  else
  {
    row= mysql_fetch_row(master);
    if (row && row[0] && row[1])
    {
      
      print_comment(md_result_file, 0,
                    "STR"
                    "STR");
      fprintf(md_result_file,
              "STR",
              comment_prefix, row[0], row[1]);
      check_io(md_result_file);
    }
    else if (!opt_force)
    {
      
      my_printf_error(0, "STR",
                      MYF(0));
      mysql_free_result(master);
      maybe_exit(EX_MYSQLERR);
      return 1;
    }
    mysql_free_result(master);
  }
  return 0;
}