static int run_mysqlcheck_upgrade(void)
{
  print_conn_args("STR");
  return run_tool(mysqlcheck_path,
                  NULL, 
                  "STR",
                  ds_args.str,
                  "STR",
                  "STR",
                  "STR",
                  opt_write_binlog ? "STR",
                  NULL);
}