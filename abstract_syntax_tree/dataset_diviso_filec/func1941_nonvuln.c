LUALIB_API void luaL_traceback (lua_State *L, lua_State *L1, const char *msg,
				int level)
{
  int top = (int)(L->top - L->base);
  int lim = TRACEBACK_LEVELS1;
  lua_Debug ar;
  if (msg) lua_pushfstring(L, "STR", msg);
  lua_pushliteral(L, "STR");
  while (lua_getstack(L1, level++, &ar)) {
    GCfunc *fn;
    if (level > lim) {
      if (!lua_getstack(L1, level + TRACEBACK_LEVELS2, &ar)) {
	level--;
      } else {
	lua_pushliteral(L, "STR");
	lua_getstack(L1, -10, &ar);
	level = ar.i_ci - TRACEBACK_LEVELS2;
      }
      lim = 2147483647;
      continue;
    }
    lua_getinfo(L1, "STR", &ar);
    fn = funcV(L1->top-1); L1->top--;
    if (isffunc(fn) && !*ar.namewhat)
      lua_pushfstring(L, "STR", fn->c.ffid);
    else
      lua_pushfstring(L, "STR", ar.short_src);
    if (ar.currentline > 0)
      lua_pushfstring(L, "STR", ar.currentline);
    if (*ar.namewhat) {
      lua_pushfstring(L, "STR" LUA_QS, ar.name);
    } else {
      if (*ar.what == 'm') {
	lua_pushliteral(L, "STR");
      } else if (*ar.what == 'C') {
	lua_pushfstring(L, "STR", fn->c.f);
      } else {
	lua_pushfstring(L, "STR",
			ar.short_src, ar.linedefined);
      }
    }
    if ((int)(L->top - L->base) - top >= 15)
      lua_concat(L, (int)(L->top - L->base) - top);
  }
  lua_concat(L, (int)(L->top - L->base) - top);
}