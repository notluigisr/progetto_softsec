static int changedline (const Proto *p, int oldpc, int newpc) {
  if (p->lineinfo == NULL)  
    return 0;
  while (oldpc++ < newpc) {
    if (p->lineinfo[oldpc] != 0)
      return (luaG_getfuncline(p, oldpc - 1) != luaG_getfuncline(p, newpc));
  }
  return 0;  
}