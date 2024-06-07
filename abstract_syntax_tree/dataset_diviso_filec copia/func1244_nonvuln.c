static void test_bug5315()
{
  MYSQL_STMT *stmt;
  const char *stmt_text;
  int rc;

  myheader("STR");

  stmt_text= "STR";
  stmt= mysql_stmt_init(mysql);
  rc= mysql_stmt_prepare(stmt, stmt_text, strlen(stmt_text));
  DIE_UNLESS(rc == 0);
  if (!opt_silent)
    printf("STR");
  mysql_change_user(mysql, opt_user, opt_password, current_db);
  if (!opt_silent)
    printf("STR");
  rc= mysql_stmt_execute(stmt);
  DIE_UNLESS(rc != 0);
  if (rc)
  {
    if (!opt_silent)
      printf("STR", mysql_stmt_error(stmt));
  }
  
  if (!opt_silent)
    printf("STR");
  mysql_stmt_close(stmt);
  if (!opt_silent)
    printf("STR");
  stmt= mysql_stmt_init(mysql);
  rc= mysql_stmt_prepare(stmt, stmt_text, strlen(stmt_text));
  DIE_UNLESS(rc == 0);
  rc= mysql_stmt_execute(stmt);
  DIE_UNLESS(rc == 0);
  mysql_stmt_close(stmt);
}