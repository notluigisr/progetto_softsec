static void usage(void)
{
  print_version();
  puts(ORACLE_WELCOME_COPYRIGHT_NOTICE("STR"));
  puts("STR");
  printf("STR", my_progname);
  my_print_help(my_long_options);
  my_print_variables(my_long_options);
  print_defaults("STR",load_default_groups);
  puts("\nWhere command is a one or more of: (Commands may be shortened)\n\
  create databasename	Create a new database\n\
  debug			Instruct server to write debug information to log\n\
  drop databasename	Delete a database and all its tables\n\
  extended-status       Gives an extended status message from the server\n\
  flush-hosts           Flush all cached hosts\n\
  flush-logs            Flush all logs\n\
  flush-status		Clear status variables\n\
  flush-tables          Flush all tables\n\
  flush-threads         Flush the thread cache\n\
  flush-privileges      Reload grant tables (same as reload)\n\
  kill id,id,...	Kill mysql threads");
#if MYSQL_VERSION_ID >= 32200
  puts("\
  password [new-password] Change old password to new-password in current format\n\
  old-password [new-password] Change old password to new-password in old format");
#endif
  puts("\
  ping			Check if mysqld is alive\n\
  processlist		Show list of active threads in server\n\
  reload		Reload grant tables\n\
  refresh		Flush all tables and close and open logfiles\n\
  shutdown		Take server down\n\
  status		Gives a short status message from the server\n\
  start-slave		Start slave\n\
  stop-slave		Stop slave\n\
  variables             Prints variables available\n\
  version		Get version info from server");
}