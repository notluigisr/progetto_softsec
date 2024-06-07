int Field_float::cmp(const uchar *a_ptr, const uchar *b_ptr)
{
  float a,b;
  float4get(a,a_ptr);
  float4get(b,b_ptr);
  return (a < b) ? -1 : (a > b) ? 1 : 0;
}