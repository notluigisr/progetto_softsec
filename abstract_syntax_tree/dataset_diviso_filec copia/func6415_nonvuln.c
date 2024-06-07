static void dbDisconnect(char *host)
{
  verbose_msg("STR");
  mysql_close(mysql);
} 