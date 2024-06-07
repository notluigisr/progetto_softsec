static void test_simple_update()
{
  MYSQL_STMT *stmt;
  int        rc;
  char       szData[25];
  int        nData= 1;
  MYSQL_RES  *result;
  MYSQL_BIND my_bind[2];
  ulong      length[2];
  char query[MAX_TEST_QUERY_LENGTH];

  myheader("STR");

  rc= mysql_autocommit(mysql, TRUE);
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR"
                         "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  verify_affected_rows(1);

  rc= mysql_commit(mysql);
  myquery(rc);

  
  my_stpcpy(query, "STR");
  stmt= mysql_simple_prepare(mysql, query);
  check_stmt(stmt);

  verify_param_count(stmt, 2);

  
  memset(my_bind, 0, sizeof(my_bind));

  nData= 1;
  my_bind[0].buffer_type= MYSQL_TYPE_STRING;
  my_bind[0].buffer= szData;                
  my_bind[0].buffer_length= sizeof(szData);
  my_bind[0].length= &length[0];
  length[0]= sprintf(szData, "STR");

  my_bind[1].buffer= (void *) &nData;
  my_bind[1].buffer_type= MYSQL_TYPE_LONG;

  rc= mysql_stmt_bind_param(stmt, my_bind);
  check_execute(stmt, rc);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);
  verify_affected_rows(1);

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