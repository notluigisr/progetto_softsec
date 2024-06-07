static void test_order_param()
{
  MYSQL_STMT *stmt;
  int rc;

  myheader("STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  stmt= mysql_simple_prepare(mysql,
                             "STR"
                             "STR"
                             "STR");
  check_stmt(stmt);
  mysql_stmt_close(stmt);

  stmt= mysql_simple_prepare(mysql,
                             "STR"
                             "STR"
                             "STR");
  check_stmt(stmt);
  mysql_stmt_close(stmt);

  stmt= mysql_simple_prepare(mysql,
                             "STR"
                             "STR"
                             "STR");
  check_stmt(stmt);
  mysql_stmt_close(stmt);

  rc= mysql_query(mysql, "STR");
  myquery(rc);
}