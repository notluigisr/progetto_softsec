void do_sync_with_master2(struct st_command *command, long offset)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL *mysql= cur_con->mysql;
  char query_buf[FN_REFLEN+128];
  int timeout= 300; 

  if (!master_pos.file[0])
    die("STR");

  sprintf(query_buf, "STR",
          master_pos.file, master_pos.pos + offset, timeout);

  if (mysql_query(mysql, query_buf))
    die("STR", query_buf, mysql_errno(mysql),
        mysql_error(mysql));

  if (!(res= mysql_store_result(mysql)))
    die("STR", query_buf);
  if (!(row= mysql_fetch_row(res)))
  {
    mysql_free_result(res);
    die("STR", query_buf);
  }

  int result= -99;
  const char* result_str= row[0];
  if (result_str)
    result= atoi(result_str);

  mysql_free_result(res);

  if (!result_str || result < 0)
  {
    
    show_query(mysql, "STR");
    show_query(mysql, "STR");
    show_query(mysql, "STR");
    fprintf(stderr, "STR");

    if (!result_str)
    {
      
      die("STR"          \
          "STR",
          command->first_word_len, command->query, query_buf);

    }

    if (result == -1)
      die("STR"            \
          "STR",
          command->first_word_len, command->query, query_buf, timeout);
    else
      die("STR",
          command->first_word_len, command->query, query_buf, result);
  }

  return;
}