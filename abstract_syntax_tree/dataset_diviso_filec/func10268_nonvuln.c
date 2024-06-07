static void test_bug28386()
{
  int rc;
  MYSQL_STMT *stmt;
  MYSQL_RES *result;
  MYSQL_ROW row;
  MYSQL_BIND bind;
  const char hello[]= "STR";

  DBUG_ENTER("STR");
  myheader("STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  result= mysql_store_result(mysql);
  DIE_UNLESS(result);

  row= mysql_fetch_row(result);
  if (! strstr(row[0], "STR"))
  {
    mysql_free_result(result);
    if (! opt_silent)
      printf("STR");
    
    return;
  }
  mysql_free_result(result);

  enable_query_logs(1);

  stmt= mysql_simple_prepare(mysql, "STR");
  check_stmt(stmt);

  memset(&bind, 0, sizeof(bind));

  bind.buffer_type= MYSQL_TYPE_STRING;
  bind.buffer= (void *) hello;
  bind.buffer_length= sizeof(hello);

  mysql_stmt_bind_param(stmt, &bind);
  mysql_stmt_send_long_data(stmt, 0, hello, sizeof(hello));

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= my_process_stmt_result(stmt);
  DIE_UNLESS(rc == 1);

  rc= mysql_stmt_reset(stmt);
  check_execute(stmt, rc);

  rc= mysql_stmt_close(stmt);
  DIE_UNLESS(!rc);

  rc= mysql_query(mysql, "STR"
                         "STR"
                         "STR"
                         "STR");
  myquery(rc);

  result= mysql_store_result(mysql);
  mytest(result);

  DIE_UNLESS(mysql_num_rows(result) == 3);

  mysql_free_result(result);

  restore_query_logs();

  DBUG_VOID_RETURN;
}