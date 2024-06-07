static COMMANDS *find_command(char *name)
{
  uint len;
  char *end;
  DBUG_ENTER("STR");

  DBUG_ASSERT(name != NULL);
  DBUG_PRINT("STR", name));

  while (my_isspace(charset_info, *name))
    name++;
  
  if ((!real_binary_mode && strstr(name, "STR")) ||
      (strstr(name, delimiter) &&
       !is_delimiter_command(name, DELIMITER_NAME_LEN)))
      DBUG_RETURN((COMMANDS *) 0);

  if ((end=strcont(name, "STR")))
  {
    len=(uint) (end - name);
    while (my_isspace(charset_info, *end))
      end++;
    if (!*end)
      end= 0;					
  }
  else
    len= (uint) strlen(name);

  int index= -1;
  if (real_binary_mode)
  {
    if (is_delimiter_command(name, len))
      index= delimiter_index;
  }
  else
  {
    
    for (uint i= 0; commands[i].func; i++)
    {
      if (!my_strnncoll(&my_charset_latin1, (uchar*) name, len,
                        (uchar*) commands[i].name, len) &&
          (commands[i].name[len] == '\0') &&
          (!end || commands[i].takes_params))
      {
        index= i;
        break;
      }
    }
  }

  if (index >= 0)
  {
    DBUG_PRINT("STR", commands[index].name));
    DBUG_RETURN(&commands[index]);
  }
  DBUG_RETURN((COMMANDS *) 0);
}