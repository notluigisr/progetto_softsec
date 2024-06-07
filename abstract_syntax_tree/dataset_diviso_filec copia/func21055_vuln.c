list_fields(MYSQL *mysql,const char *db,const char *table,
	    const char *wild)
{
  char query[1024],*end;
  MYSQL_RES *result;
  MYSQL_ROW row;
  ulong UNINIT_VAR(rows);

  if (mysql_select_db(mysql,db))
  {
    fprintf(stderr,"STR",my_progname,db,
	    mysql_error(mysql));
    return 1;
  }

  if (opt_count)
  {
    sprintf(query,"STR", table);
    if (mysql_query(mysql,query) || !(result=mysql_store_result(mysql)))
    {
      fprintf(stderr,"STR",
              my_progname,db,table,mysql_error(mysql));
      return 1;
    }
    row= mysql_fetch_row(result);
    rows= (ulong) strtoull(row[0], (char**) 0, 10);
    mysql_free_result(result);
  }

  end=strmov(strmov(strmov(query,"STR");
  if (wild && wild[0])
    strxmov(end,"STR",NullS);
  if (mysql_query(mysql,query) || !(result=mysql_store_result(mysql)))
  {
    fprintf(stderr,"STR",
	    my_progname,db,table,mysql_error(mysql));
    return 1;
  }

  printf("STR", db, table);
  if (opt_count)
    printf("STR", rows);
  if (wild && wild[0])
    printf("STR",wild);
  putchar('\n');

  print_res_header(result);
  while ((row=mysql_fetch_row(result)))
    print_res_row(result,row);
  print_res_top(result);
  if (opt_show_keys)
  {
    end=strmov(strmov(strmov(query,"STR");
    if (mysql_query(mysql,query) || !(result=mysql_store_result(mysql)))
    {
      fprintf(stderr,"STR",
	      my_progname,db,table,mysql_error(mysql));
      return 1;
    }
    if (mysql_num_rows(result))
    {
      print_res_header(result);
      while ((row=mysql_fetch_row(result)))
	print_res_row(result,row);
      print_res_top(result);
    }
    else
      puts("STR");
  }
  mysql_free_result(result);
  return 0;
}