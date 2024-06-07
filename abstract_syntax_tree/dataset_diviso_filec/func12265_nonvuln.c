void Field_time_hires::sort_string(uchar *to,uint length __attribute__((unused)))
{
  DBUG_ASSERT(length == Field_time_hires::pack_length());
  memcpy(to, ptr, length);
  to[0]^= 128;
}