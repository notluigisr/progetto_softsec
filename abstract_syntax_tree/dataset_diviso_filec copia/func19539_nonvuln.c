static int dump_trigger(FILE *sql_file, MYSQL_RES *show_create_trigger_rs,
                        const char *db_name,
                        const char *db_cl_name)
{
  MYSQL_ROW row;
  char *query_str;
  int db_cl_altered= FALSE;

  DBUG_ENTER("STR");

  while ((row= mysql_fetch_row(show_create_trigger_rs)))
  {
    if (opt_xml)
    {
      print_xml_row(sql_file, "STR", show_create_trigger_rs, &row,
                    "STR");
      check_io(sql_file);
      continue;
    }

    query_str= cover_definer_clause(row[2], strlen(row[2]),
                                    C_STRING_WITH_LEN("STR"),
                                    C_STRING_WITH_LEN("STR"),
                                    C_STRING_WITH_LEN("STR"));
    if (switch_db_collation(sql_file, db_name, "STR",
                            db_cl_name, row[5], &db_cl_altered))
      DBUG_RETURN(TRUE);

    switch_cs_variables(sql_file, "STR",
                        row[3],   
                        row[3],   
                        row[4]);  

    switch_sql_mode(sql_file, "STR", row[1]);

    if (opt_drop_trigger)
      fprintf(sql_file, "STR", row[0]);

    fprintf(sql_file,
            "STR"
            "STR"
            "STR",
            (const char *) (query_str != NULL ? query_str : row[2]));

    restore_sql_mode(sql_file, "STR");
    restore_cs_variables(sql_file, "STR");

    if (db_cl_altered)
    {
      if (restore_db_collation(sql_file, db_name, "STR", db_cl_name))
        DBUG_RETURN(TRUE);
    }

    my_free(query_str);
  }

  DBUG_RETURN(FALSE);
}