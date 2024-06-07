static void controloptions (lua_State *L, int opt, const char **fmt,
                            Header *h) {
  switch (opt) {
    case  ' ': return;  
    case '>': h->endian = BIG; return;
    case '<': h->endian = LITTLE; return;
    case '!': {
      int a = getnum(fmt, MAXALIGN);
      if (!isp2(a))
        luaL_error(L, "STR", a);
      h->align = a;
      return;
    }
    default: {
      const char *msg = lua_pushfstring(L, "STR", opt);
      luaL_argerror(L, 1, msg);
    }
  }
}