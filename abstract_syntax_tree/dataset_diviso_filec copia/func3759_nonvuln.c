static void test_prepare_field_result()
{
  MYSQL_STMT *stmt;
  MYSQL_RES  *result;
  int        rc;
  char query[MAX_TEST_QUERY_LENGTH];

  myheader("STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR"
                         "STR"
                         "STR");
  myquery(rc);

  
  strmov(query, "STR"
                "STR");
  stmt= mysql_simple_prepare(mysql, query);
  check_stmt(stmt);

  verify_param_count(stmt, 1);

  result= mysql_stmt_result_metadata(stmt);
  mytest(result);

  my_print_result_metadata(result);

  if (!opt_silent)
    fprintf(stdout, "STR");
  verify_prepare_field(result, 0, "STR", MYSQL_TYPE_LONG,
                       "STR", current_db, 11, 0);
  verify_prepare_field(result, 1, "STR", MYSQL_TYPE_VAR_STRING,
                       "STR", current_db, 50, 0);
  verify_prepare_field(result, 2, "STR", MYSQL_TYPE_DATE,
                       "STR", current_db, 10, 0);
  verify_prepare_field(result, 3, "STR", MYSQL_TYPE_TIMESTAMP,
                       "STR", current_db, 19, 0);
  verify_prepare_field(result, 4, "STR",
                       (mysql_get_server_version(mysql) <= 50000 ?
                        MYSQL_TYPE_VAR_STRING : MYSQL_TYPE_STRING),
                       "STR", current_db, 4, 0);

  verify_field_count(result, 5);
  mysql_free_result(result);
  mysql_stmt_close(stmt);
}