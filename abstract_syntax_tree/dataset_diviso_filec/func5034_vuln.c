static int getnum (lua_State *L, const char **fmt, int df) {
  if (!isdigit(**fmt))  
    return df;  
  else {
    int a = 0;
    do {
      if (a > (INT_MAX / 10) || a * 10 > (INT_MAX - (**fmt - '0')))
        luaL_error(L, "STR");
      a = a*10 + *((*fmt)++) - '0';
    } while (isdigit(**fmt));
    return a;
  }
}