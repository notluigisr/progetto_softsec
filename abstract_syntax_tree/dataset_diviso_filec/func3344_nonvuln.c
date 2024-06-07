static void test_bug12243()
{
  MYSQL_STMT *stmt1, *stmt2;
  int rc;
  const char *stmt_text;
  ulong type;

  myheader("STR");

  if (! have_innodb)
  {
    if (!opt_silent)
      printf("STR");
    return;
  }

  
  mysql_query(mysql, "STR");
  mysql_query(mysql, "STR");
  rc= mysql_query(mysql, "STR");
  myquery(rc);
  mysql_autocommit(mysql, FALSE);
  
  stmt1= mysql_stmt_init(mysql);
  stmt2= mysql_stmt_init(mysql);
  type= (ulong) CURSOR_TYPE_READ_ONLY;
  mysql_stmt_attr_set(stmt1, STMT_ATTR_CURSOR_TYPE, (const void*) &type);
  mysql_stmt_attr_set(stmt2, STMT_ATTR_CURSOR_TYPE, (const void*) &type);

  stmt_text= "STR";

  rc= mysql_stmt_prepare(stmt1, stmt_text, strlen(stmt_text));
  check_execute(stmt1, rc);
  rc= mysql_stmt_execute(stmt1);
  check_execute(stmt1, rc);
  rc= mysql_stmt_fetch(stmt1);
  check_execute(stmt1, rc);

  rc= mysql_stmt_prepare(stmt2, stmt_text, strlen(stmt_text));
  check_execute(stmt2, rc);
  rc= mysql_stmt_execute(stmt2);
  check_execute(stmt2, rc);
  rc= mysql_stmt_fetch(stmt2);
  check_execute(stmt2, rc);

  rc= mysql_stmt_close(stmt1);
  check_execute(stmt1, rc);
  rc= mysql_commit(mysql);
  myquery(rc);
  rc= mysql_stmt_fetch(stmt2);
  check_execute(stmt2, rc);

  mysql_stmt_close(stmt2);
  rc= mysql_query(mysql, "STR");
  myquery(rc);
  mysql_autocommit(mysql, TRUE);                
}