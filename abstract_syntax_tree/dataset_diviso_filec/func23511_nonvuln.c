CAMLexport value caml_alloc_tuple(mlsize_t n)
{
  return caml_alloc(n, 0);
}