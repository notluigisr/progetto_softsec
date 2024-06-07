static int traversethread (global_State *g, lua_State *th) {
  UpVal *uv;
  StkId o = th->stack;
  if (o == NULL)
    return 1;  
  lua_assert(g->gcstate == GCSatomic ||
             th->openupval == NULL || isintwups(th));
  for (; o < th->top; o++)  
    markvalue(g, s2v(o));
  for (uv = th->openupval; uv != NULL; uv = uv->u.open.next)
    markobject(g, uv);  
  if (g->gcstate == GCSatomic) {  
    StkId lim = th->stack + th->stacksize;  
    for (; o < lim; o++)  
      setnilvalue(s2v(o));
    
    if (!isintwups(th) && th->openupval != NULL) {
      th->twups = g->twups;  
      g->twups = th;
    }
  }
  else if (!g->gcemergency)
    luaD_shrinkstack(th); 
  return 1 + th->stacksize;
}