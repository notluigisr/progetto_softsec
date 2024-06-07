skip_short_body (int fd, wgint contlen, bool chunked)
{
  enum {
    SKIP_SIZE = 512,                
    SKIP_THRESHOLD = 4096        
  };
  wgint remaining_chunk_size = 0;
  char dlbuf[SKIP_SIZE + 1];
  dlbuf[SKIP_SIZE] = '\0';        

  
  if (contlen > SKIP_THRESHOLD)
    return false;

  while (contlen > 0 || chunked)
    {
      int ret;
      if (chunked)
        {
          if (remaining_chunk_size == 0)
            {
              char *line = fd_read_line (fd);
              char *endl;
              if (line == NULL)
                break;

              remaining_chunk_size = strtol (line, &endl, 16);
              xfree (line);

              if (remaining_chunk_size == 0)
                {
                  line = fd_read_line (fd);
                  xfree (line);
                  break;
                }
            }

          contlen = MIN (remaining_chunk_size, SKIP_SIZE);
        }

      DEBUGP (("STR", number_to_static_string (contlen)));

      ret = fd_read (fd, dlbuf, MIN (contlen, SKIP_SIZE), -1);
      if (ret <= 0)
        {
          
          DEBUGP (("STR",
                   ret < 0 ? fd_errstr (fd) : "STR"));
          return false;
        }
      contlen -= ret;

      if (chunked)
        {
          remaining_chunk_size -= ret;
          if (remaining_chunk_size == 0)
            {
              char *line = fd_read_line (fd);
              if (line == NULL)
                return false;
              else
                xfree (line);
            }
        }

      
      DEBUGP (("STR", ret, dlbuf));
    }

  DEBUGP (("STR"));
  return true;
}