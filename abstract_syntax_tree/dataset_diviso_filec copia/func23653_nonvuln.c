int luaV_flttointeger (lua_Number n, lua_Integer *p, F2Imod mode) {
  lua_Number f = l_floor(n);
  if (n != f) {  
    if (mode == F2Ieq) return 0;  
    else if (mode == F2Iceil)  
      f += 1;  
  }
  return lua_numbertointeger(f, p);
}