CAMLprim value caml_input_value(value vchan)
{
  CAMLparam1 (vchan);
  struct channel * chan = Channel(vchan);
  CAMLlocal1 (res);

  Lock(chan);
  res = caml_input_val(chan);
  Unlock(chan);
  CAMLreturn (res);
}