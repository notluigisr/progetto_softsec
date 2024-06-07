static void voutf(struct GlobalConfig *config,
                  const char *prefix,
                  const char *fmt,
                  va_list ap)
{
  size_t width = (79 - strlen(prefix));
  if(!config->mute) {
    size_t len;
    char *ptr;
    char print_buffer[256];

    len = vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);

    ptr = print_buffer;
    while(len > 0) {
      fputs(prefix, config->errors);

      if(len > width) {
        size_t cut = width-1;

        while(!ISSPACE(ptr[cut]) && cut) {
          cut--;
        }
        if(0 == cut)
          
          cut = width-1;

        (void)fwrite(ptr, cut + 1, 1, config->errors);
        fputs("STR", config->errors);
        ptr += cut + 1; 
        len -= cut;
      }
      else {
        fputs(ptr, config->errors);
        len = 0;
      }
    }
  }
}