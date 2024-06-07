MYSQL *mysql_connect_ssl_check(MYSQL *mysql_arg, const char *host,
                               const char *user, const char *passwd,
                               const char *db, uint port,
                               const char *unix_socket, ulong client_flag,
                               my_bool ssl_required MY_ATTRIBUTE((unused)))
{
  MYSQL *mysql= mysql_real_connect(mysql_arg, host, user, passwd, db, port,
                                   unix_socket, client_flag);
#if defined(HAVE_OPENSSL) && !defined(EMBEDDED_LIBRARY)
  if (mysql &&                                   
      ssl_required &&                            
      !mysql_get_ssl_cipher(mysql))              
  {
    NET *net= &mysql->net;
    net->last_errno= CR_SSL_CONNECTION_ERROR;
    strmov(net->last_error, "STR");
    strmov(net->sqlstate, "STR");
    return NULL;
  }
#endif
  return mysql;
}