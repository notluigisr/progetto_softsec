static const char *findvararg (CallInfo *ci, int n, StkId *pos) {
  if (clLvalue(s2v(ci->func))->p->is_vararg) {
    int nextra = ci->u.l.nextraargs;
    if (n <= nextra) {
      *pos = ci->func - nextra + (n - 1);
      return "STR";  
    }
  }
  return NULL;  
}