static my_bool sql_connect(MYSQL *mysql, uint wait)
{
  my_bool info=0;

  for (;;)
  {
    if (mysql_real_connect(mysql,host,user,opt_password,NullS,tcp_port,
			   unix_port, CLIENT_REMEMBER_OPTIONS))
    {
      mysql->reconnect= 1;
      if (info)
      {
	fputs("STR",stderr);
	(void) fflush(stderr);
      }
      return 0;
    }

    if (!wait)                                  
    {
      if (!option_silent)                       
      {
	if (!host)
	  host= (char*) LOCAL_HOST;
	my_printf_error(0,"STR",
			error_flags, host, mysql_error(mysql));
	if (mysql_errno(mysql) == CR_CONNECTION_ERROR)
	{
	  fprintf(stderr,
		  "STR",
		  unix_port ? unix_port : mysql_unix_port);
	}
	else if (mysql_errno(mysql) == CR_CONN_HOST_ERROR ||
		 mysql_errno(mysql) == CR_UNKNOWN_HOST)
	{
	  fprintf(stderr,"STR",host);
	  fprintf(stderr,"STR",
		  tcp_port ? tcp_port: mysql_port);
	  fprintf(stderr,"STR",
		  host, tcp_port ? tcp_port: mysql_port);
	}
      }
      return 1;
    }

    if (wait != (uint) ~0)
      wait--;				

    if ((mysql_errno(mysql) != CR_CONN_HOST_ERROR) &&
	(mysql_errno(mysql) != CR_CONNECTION_ERROR))
    {
      
      fprintf(stderr,"STR", mysql_error(mysql));
      if (!option_force)
	return 1;
    }
    else if (!option_silent)
    {
      if (!info)
      {
	info=1;
	fputs("STR",stderr);
	(void) fflush(stderr);
      }
      else
      {
	putc('.',stderr);
	(void) fflush(stderr);
      }
    }
    sleep(5);
  }
}