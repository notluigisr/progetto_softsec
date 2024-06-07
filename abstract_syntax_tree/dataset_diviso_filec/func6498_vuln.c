void luaD_callnoyield (lua_State *L, StkId func, int nResults) {
  incXCcalls(L);
  if (getCcalls(L) <= CSTACKERR)  
    luaE_freeCI(L);
  luaD_call(L, func, nResults);
  decXCcalls(L);
}