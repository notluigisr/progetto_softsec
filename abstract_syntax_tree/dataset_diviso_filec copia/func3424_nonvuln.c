
static size_t get_length_store_length(size_t length)
{
  
  
  uchar length_buffer[MAX_VARIABLE_STRING_LENGTH], *ptr;

  ptr= net_store_length(length_buffer, length);

  return ptr - &length_buffer[0];