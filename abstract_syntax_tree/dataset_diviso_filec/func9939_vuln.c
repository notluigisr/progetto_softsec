char *get_56_lenc_string(char **buffer,
                         size_t *max_bytes_available,
                         size_t *string_length)
{
  static char empty_string[1]= { '\0' };
  char *begin= *buffer;

  if (*max_bytes_available == 0)
    return NULL;

  
  if (*begin == 0)
  {
    *string_length= 0;
    --*max_bytes_available;
    ++*buffer;
    
    return empty_string;
  }

  *string_length= (size_t)net_field_length_ll((uchar **)buffer);

  DBUG_EXECUTE_IF("STR",
                  *string_length= SIZE_T_MAX;
  );

  size_t len_len= (size_t)(*buffer - begin);
  
  if (*string_length > *max_bytes_available - len_len)
    return NULL;

  *max_bytes_available -= *string_length;
  *max_bytes_available -= len_len;
  *buffer += *string_length;
  return (char *)(begin + len_len);
}