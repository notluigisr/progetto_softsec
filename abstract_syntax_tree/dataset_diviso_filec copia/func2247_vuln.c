static void process_event_record(MYSQL_THD thd, LEX_CSTRING event_name,
                                 const char *data, size_t data_length)
{
  const char *record_str = (const char *)THDVAR(thd, event_record_def);
  LEX_CSTRING record_begin = get_token(&record_str);
  LEX_CSTRING record_end = get_token(&record_str);

  if (record_str == NULL)
  {
    return;
  }

  if (record_end.length == 0)
  {
    

    const char *buffer= THDVAR(thd, event_record);

    
    add_event(thd, buffer, event_name, data, data_length);


    if (!my_charset_latin1.coll->strnncoll(&my_charset_latin1,
                                           (const uchar *)record_begin.str,
                                           record_begin.length,
                                           (const uchar *)event_name.str,
                                           event_name.length, FALSE))
    {
      
      THDVAR(thd, event_record_def)= 0;
    }
  }
  else
  {
    
    if (my_charset_latin1.coll->strnncoll(&my_charset_latin1,
                                          (const uchar *)record_begin.str,
                                          record_begin.length,
                                          (const uchar *)event_name.str,
                                          event_name.length, FALSE))
    {
      
      return;
    }

    THDVAR(thd, event_record)= 0;

    add_event(thd, "", event_name, data, data_length);

    

    record_str = (const char *)THDVAR(thd, event_record_def);

    
    memmove((char *)record_str, (void *)record_end.str, record_end.length + 1);
  }
}