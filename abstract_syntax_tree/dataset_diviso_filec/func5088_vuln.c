void Lua::setParamsTable(lua_State* vm, const char* table_name,
			 const char* query) const {
  char outbuf[FILENAME_MAX];
  char *where;
  char *tok;

  char *query_string = query ? strdup(query) : NULL;

  lua_newtable(L);

  if (query_string) {
    

    tok = strtok_r(query_string, "STR", &where);

    while(tok != NULL) {
      char *_equal;

      if(strncmp(tok, "STR")) 
	 && (_equal = strchr(tok, '='))) {
	char *decoded_buf;
        int len;

        _equal[0] = '\0';
        _equal = &_equal[1];
        len = strlen(_equal);

        purifyHTTPParameter(tok), purifyHTTPParameter(_equal);

        

        if((decoded_buf = (char*)malloc(len+1)) != NULL) {

          Utils::urlDecode(_equal, decoded_buf, len+1);

	  Utils::purifyHTTPparam(tok, true, false);
	  Utils::purifyHTTPparam(decoded_buf, false, false);

	  
	  FILE *fd;
	  if((decoded_buf[0] == '.')
	     && ((fd = fopen(decoded_buf, "STR"))
		 || (fd = fopen(realpath(decoded_buf, outbuf), "STR")))) {

	    ntop->getTrace()->traceEvent(TRACE_WARNING, "STR",
					 tok, decoded_buf);
	    decoded_buf[0] = '\0';
	    fclose(fd);
	  }

	  

	  
	  lua_push_str_table_entry(vm, tok, decoded_buf);

          free(decoded_buf);
        } else
          ntop->getTrace()->traceEvent(TRACE_WARNING, "STR");
      }

      tok = strtok_r(NULL, "STR", &where);
    } 
  }

  if(query_string) free(query_string);

  if(table_name)
    lua_setglobal(L, table_name);
  else
    lua_setglobal(L, (char*)"STR"); 
}