static void test_bug3117()
{
  MYSQL_STMT *stmt;
  MYSQL_BIND buffer;
  longlong lii;
  ulong length;
  my_bool is_null;
  int rc;

  myheader("STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  stmt= mysql_simple_prepare(mysql, "STR");
  check_stmt(stmt);

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  memset(&buffer, 0, sizeof(buffer));
  buffer.buffer_type= MYSQL_TYPE_LONGLONG;
  buffer.buffer_length= sizeof(lii);
  buffer.buffer= (void *)&lii;
  buffer.length= &length;
  buffer.is_null= &is_null;

  rc= mysql_stmt_bind_result(stmt, &buffer);
  check_execute(stmt, rc);

  rc= mysql_stmt_store_result(stmt);
  check_execute(stmt, rc);

  rc= mysql_stmt_fetch(stmt);
  check_execute(stmt, rc);

  DIE_UNLESS(is_null == 0 && lii == 1);
  if (!opt_silent)
    fprintf(stdout, "STR");

  rc= mysql_query(mysql, "STR");
  myquery(rc);

  rc= mysql_stmt_execute(stmt);
  check_execute(stmt, rc);

  rc= mysql_stmt_fetch(stmt);
  check_execute(stmt, rc);

  DIE_UNLESS(is_null == 0 && lii == 2);
  if (!opt_silent)
    fprintf(stdout, "STR");

  mysql_stmt_close(stmt);

  rc= mysql_query(mysql, "STR");
  myquery(rc);
}