static void test_bug12744()
{
  MYSQL_STMT *prep_stmt = NULL;
  MYSQL *lmysql;
  int rc;
  myheader("STR");

  lmysql= mysql_client_init(NULL);
  DIE_UNLESS(lmysql);

  if (!mysql_real_connect(lmysql, opt_host, opt_user, opt_password,
                          current_db, opt_port, opt_unix_socket, 0))
  {
    fprintf(stderr, "STR");
    DIE_UNLESS(0);
  }

  prep_stmt= mysql_stmt_init(lmysql);
  rc= mysql_stmt_prepare(prep_stmt, "STR", 8);
  DIE_UNLESS(rc == 0);

  mysql_close(lmysql);

  rc= mysql_stmt_execute(prep_stmt);
  DIE_UNLESS(rc);
  rc= mysql_stmt_reset(prep_stmt);
  DIE_UNLESS(rc);
  rc= mysql_stmt_close(prep_stmt);
  DIE_UNLESS(rc == 0);
}