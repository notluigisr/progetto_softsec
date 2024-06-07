void do_wait_for_slave_to_stop(struct st_command *c __attribute__((unused)))
{
  static int SLAVE_POLL_INTERVAL= 300000;
  MYSQL* mysql = cur_con->mysql;
  for (;;)
  {
    MYSQL_RES *UNINIT_VAR(res);
    MYSQL_ROW row;
    int done;

    if (mysql_query(mysql,"STR") ||
	!(res=mysql_store_result(mysql)))
      die("STR",
	  mysql_error(mysql));
    if (!(row=mysql_fetch_row(res)) || !row[1])
    {
      mysql_free_result(res);
      die("STR");
    }
    done = !strcmp(row[1],"STR");
    mysql_free_result(res);
    if (done)
      break;
    my_sleep(SLAVE_POLL_INTERVAL);
  }
  return;
}