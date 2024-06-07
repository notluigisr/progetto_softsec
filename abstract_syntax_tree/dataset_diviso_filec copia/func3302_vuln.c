static void write_header(FILE *sql_file, char *db_name)
{
  if (opt_xml)
  {
    fputs("STR", sql_file);
    
    fputs("STR", sql_file);
    fputs("STR",
          sql_file);
    fputs("STR", sql_file);
    check_io(sql_file);
  }
  else if (!opt_compact)
  {
    print_comment(sql_file, 0,
                  "STR",
                  DUMP_VERSION, MYSQL_SERVER_VERSION, SYSTEM_TYPE,
                  MACHINE_TYPE);
    print_comment(sql_file, 0, "STR",
                  current_host ? current_host : "STR",
                  db_name ? db_name : "");
    print_comment(sql_file, 0,
                  "STR"
                 );
    print_comment(sql_file, 0, "STR",
                  mysql_get_server_info(&mysql_connection));

    if (opt_set_charset)
      fprintf(sql_file,
"STR"
"STR"
"STR"
"STR",default_charset);

    if (opt_tz_utc)
    {
      fprintf(sql_file, "STR");
      fprintf(sql_file, "STR");
    }

    if (!path)
    {
      fprintf(md_result_file,"\
;\n\
;\n\
");
    }
    fprintf(sql_file,
            "STR"
            "STR",
            path?"STR",
            compatible_mode_normal_str);
    check_io(sql_file);
  }
} 