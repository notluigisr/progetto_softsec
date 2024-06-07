int lua_resetthread (lua_State *L) {
  CallInfo *ci;
  int status;
  lua_lock(L);
  L->ci = ci = &L->base_ci;  
  setnilvalue(s2v(L->stack));  
  ci->func = L->stack;
  ci->callstatus = CIST_C;
  status = luaF_close(L, L->stack, CLOSEPROTECT);
  if (status != CLOSEPROTECT)  
    luaD_seterrorobj(L, status, L->stack + 1);
  else {
    status = LUA_OK;
    L->top = L->stack + 1;
  }
  ci->top = L->top + LUA_MINSTACK;
  L->status = status;
  lua_unlock(L);
  return status;
}