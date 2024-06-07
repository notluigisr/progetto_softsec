static void mbed_debug(void *context, int level, const char *f_name,
                       int line_nb, const char *line)
{
  struct SessionHandle *data = NULL;

  if(!context)
    return;

  data = (struct SessionHandle *)context;

  infof(data, "STR", line);
  (void) level;
}