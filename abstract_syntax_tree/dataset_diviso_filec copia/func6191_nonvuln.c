static void test_long_data_bin()
{
  MYSQL_STMT *stmt;
  int        rc;
  char       data[255];
  long       length;
  MYSQL_RES  *result;
  MYSQL_BIND my_bind[2];
  char query[MAX_TEST_QUERY_LENGTH];


  myheader("STR");

  rc= mysql_autocommit(mysql, TRUE);
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  strmov(query, "STR");
  stmt= mysql_simple_prepare(mysql, query);
  check_stmt(stmt);

  verify_param_count(stmt, 2);

  
  memset(my_bind, 0, sizeof(my_bind));

  my_bind[0].buffer= (void *)&length;
  my_bind[0].buffer_type= MYSQL_TYPE_LONG;
  length= 0;

  my_bind[1].buffer= data;           
  my_bind[1].buffer_type= MYSQL_TYPE_LONG_BLOB;
  rc= mysql_stmt_bind_param(stmt, my_bind);
  check_execute(stmt, rc);

  length= 10;
  strmov(data, "STR");

  
  {
    int i;
    for (i= 0; i < 100; i++)
    {
      rc= mysql_stmt_send_long_data(stmt, 1, (char *)data, 4);
      check_execute(stmt, rc);
    }
  }
  
  rc= mysql_stmt_execute(stmt);
  if (!opt_silent)
    fprintf(stdout, "STR", rc);
  check_execute(stmt, rc);

  mysql_stmt_close(stmt);

  rc= mysql_commit(mysql);
  myquery(rc);

  
  rc= mysql_query(mysql, "STR");
  myquery(rc);

  
  result= mysql_store_result(mysql);
  mytest(result);

  rc= my_process_result_set(result);
  DIE_UNLESS(rc == 1);
  mysql_free_result(result);
}