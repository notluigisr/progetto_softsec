char check_if_ignore_table(const char *table_name, char *table_type)
{
  char result= IGNORE_NONE;
  char buff[FN_REFLEN+80], show_name_buff[FN_REFLEN];
  MYSQL_RES *res= NULL;
  MYSQL_ROW row;
  DBUG_ENTER("STR");

  
  DBUG_ASSERT(2*sizeof(table_name) < sizeof(show_name_buff));
  my_snprintf(buff, sizeof(buff), "STR",
              quote_for_like(table_name, show_name_buff));
  if (mysql_query_with_error_report(mysql, &res, buff))
  {
    if (mysql_errno(mysql) != ER_PARSE_ERROR)
    {                                   
      verbose_msg("STR"
                  "STR", table_name, mysql_error(mysql));
      DBUG_RETURN(result);                       
    }
  }
  if (!(row= mysql_fetch_row(res)))
  {
    fprintf(stderr,
            "STR",
            table_name, mysql_error(mysql));
    mysql_free_result(res);
    DBUG_RETURN(result);                         
  }
  if (!(row[1]))
    strmake(table_type, "STR", NAME_LEN-1);
  else
  {
    
    strmake(table_type, row[1], NAME_LEN-1);
    if (opt_delayed)
    {
      if (strcmp(table_type,"STR") &&
          strcmp(table_type,"STR") &&
          strcmp(table_type,"STR") &&
          strcmp(table_type,"STR") &&
          strcmp(table_type,"STR"))
        result= IGNORE_INSERT_DELAYED;
    }

    
    if (!opt_no_data &&
        (!my_strcasecmp(&my_charset_latin1, table_type, "STR") ||
         !strcmp(table_type,"STR") ||
         !strcmp(table_type,"STR")))
      result= IGNORE_DATA;
  }
  mysql_free_result(res);
  DBUG_RETURN(result);
}