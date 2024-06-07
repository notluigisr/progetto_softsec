void Field_date::sort_string(uchar *to,uint length __attribute__((unused)))
{
  to[0] = ptr[3];
  to[1] = ptr[2];
  to[2] = ptr[1];
  to[3] = ptr[0];
}