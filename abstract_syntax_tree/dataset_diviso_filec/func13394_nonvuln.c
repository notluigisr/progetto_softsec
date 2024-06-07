LJ_NOINLINE void LJ_FASTCALL lj_err_throw(lua_State *L, int errcode)
{
  global_State *g = G(L);
  lj_trace_abort(g);
  setgcrefnull(g->jit_L);
  L->status = 0;
#if LJ_UNWIND_EXT
  err_raise_ext(errcode);
  
  if (G(L)->panic)
    G(L)->panic(L);
#else
  {
    void *cf = err_unwind(L, NULL, errcode);
    if (cframe_unwind_ff(cf))
      lj_vm_unwind_ff(cframe_raw(cf));
    else
      lj_vm_unwind_c(cframe_raw(cf), errcode);
  }
#endif
  exit(EXIT_FAILURE);
}