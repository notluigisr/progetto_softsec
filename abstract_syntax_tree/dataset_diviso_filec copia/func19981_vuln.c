list_table_status(MYSQL *mysql,const char *db,const char *wild)
{
  char query[1024],*end;
  MYSQL_RES *result;
  MYSQL_ROW row;

  end=strxmov(query,"STR",NullS);
  if (wild && wild[0])
    strxmov(end,"STR",NullS);
  if (mysql_query(mysql,query) || !(result=mysql_store_result(mysql)))
  {
    fprintf(stderr,"STR",
	    my_progname,db,wild ? wild : "",mysql_error(mysql));
    if (mysql_errno(mysql) == ER_PARSE_ERROR)
      fprintf(stderr,"STR");
    return 1;
  }

  printf("STR",db);
  if (wild)
    printf("STR",wild);
  putchar('\n');

  print_res_header(result);
  while ((row=mysql_fetch_row(result)))
    print_res_row(result,row);
  print_res_top(result);
  mysql_free_result(result);
  return 0;
}