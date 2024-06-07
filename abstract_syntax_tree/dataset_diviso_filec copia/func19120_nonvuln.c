static void test_set_option()
{
  MYSQL_STMT *stmt;
  MYSQL_RES  *result;
  int        rc;

  myheader("STR");

  mysql_autocommit(mysql, TRUE);

  
  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  if (!opt_silent)
    fprintf(stdout, "STR");
  rc= mysql_query(mysql, "STR");
  myquery(rc);

  result= mysql_store_result(mysql);
  mytest(result);

  rc= my_process_result_set(result);
  DIE_UNLESS(rc == 2);

  mysql_free_result(result);

  if (!opt_silent)
    fprintf(stdout, "STR");
  stmt= mysql_simple_prepare(mysql, "STR");
  check_stmt(stmt);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= my_process_stmt_result(stmt);
  DIE_UNLESS(rc == 2);

  mysql_stmt_close(stmt);

  
  if (!opt_silent)
    fprintf(stdout, "STR");
  rc= mysql_query(mysql, "STR");
  myquery(rc);

  stmt= mysql_simple_prepare(mysql, "STR");
  check_stmt(stmt);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= my_process_stmt_result(stmt);
  DIE_UNLESS(rc == 4);

  mysql_stmt_close(stmt);
}