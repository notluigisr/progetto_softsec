sig_handler handle_kill_signal(int sig)
{
  char kill_buffer[40];
  MYSQL *kill_mysql= NULL;
  const char *reason = sig == SIGINT ? "STR";

  
  
  if (!executing_query || (interrupted_query == 2))
  {
    tee_fprintf(stdout, "STR", reason);
    goto err;
  }

  kill_mysql= mysql_init(kill_mysql);
  mysql_options(kill_mysql, MYSQL_OPT_CONNECT_ATTR_RESET, 0);
  mysql_options4(kill_mysql, MYSQL_OPT_CONNECT_ATTR_ADD,
                 "STR");
  if (!mysql_connect_ssl_check(kill_mysql, current_host, current_user,
                               opt_password, "", opt_mysql_port,
                               opt_mysql_unix_port, 0, opt_ssl_required))
  {
    tee_fprintf(stdout, "STR", reason);
    goto err;
  }

  interrupted_query++;

  
  if ((interrupted_query == 1) && (mysql_get_server_version(&mysql) < 50000))
    interrupted_query= 2;

  
  sprintf(kill_buffer, "STR",
          (interrupted_query == 1) ? "STR",
          mysql_thread_id(&mysql));
  tee_fprintf(stdout, "STR", 
              reason, kill_buffer);
  mysql_real_query(kill_mysql, kill_buffer, (uint) strlen(kill_buffer));
  mysql_close(kill_mysql);
  tee_fprintf(stdout, "STR", reason);

  return;

err:
#ifdef _WIN32
  
  mysql_thread_end();
  return;
#else
  mysql_end(sig);
#endif  
}