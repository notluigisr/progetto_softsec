fiber_yield(mrb_state *mrb, mrb_value self)
{
  const mrb_value *a;
  mrb_int len;

  mrb_get_args(mrb, "STR", &a, &len);
  return mrb_fiber_yield(mrb, len, a);
}