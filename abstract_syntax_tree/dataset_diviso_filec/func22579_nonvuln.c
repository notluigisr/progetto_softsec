static void test_opt_reconnect()
{
  MYSQL *lmysql;
  my_bool my_true= TRUE;

  myheader("STR");

  if (!(lmysql= mysql_client_init(NULL)))
  {
    myerror("STR");
    exit(1);
  }

  if (!opt_silent)
    fprintf(stdout, "STR", lmysql->reconnect);
  DIE_UNLESS(lmysql->reconnect == 0);

  if (mysql_options(lmysql, MYSQL_OPT_RECONNECT, &my_true))
  {
    myerror("STR");
    DIE_UNLESS(0);
  }

  
  if (!opt_silent)
    fprintf(stdout, "STR", lmysql->reconnect);
  DIE_UNLESS(lmysql->reconnect == 1);

  if (!(mysql_real_connect(lmysql, opt_host, opt_user,
                           opt_password, current_db, opt_port,
                           opt_unix_socket, 0)))
  {
    myerror("STR");
    DIE_UNLESS(0);
  }

  
  if (!opt_silent)
    fprintf(stdout, "STR",
	    lmysql->reconnect);
  DIE_UNLESS(lmysql->reconnect == 1);

  mysql_close(lmysql);

  if (!(lmysql= mysql_client_init(NULL)))
  {
    myerror("STR");
    DIE_UNLESS(0);
  }

  if (!opt_silent)
    fprintf(stdout, "STR", lmysql->reconnect);
  DIE_UNLESS(lmysql->reconnect == 0);

  if (!(mysql_real_connect(lmysql, opt_host, opt_user,
                           opt_password, current_db, opt_port,
                           opt_unix_socket, 0)))
  {
    myerror("STR");
    DIE_UNLESS(0);
  }

  
  if (!opt_silent)
    fprintf(stdout, "STR",
	    lmysql->reconnect);
  DIE_UNLESS(lmysql->reconnect == 0);

  mysql_close(lmysql);
}