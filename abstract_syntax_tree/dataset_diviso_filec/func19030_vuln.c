static int remarkupvals (global_State *g) {
  lua_State *thread;
  lua_State **p = &g->twups;
  int work = 0;
  while ((thread = *p) != NULL) {
    work++;
    lua_assert(!isblack(thread));  
    if (isgray(thread) && thread->openupval != NULL)
      p = &thread->twups;  
    else {  
      UpVal *uv;
      *p = thread->twups;  
      thread->twups = thread;  
      for (uv = thread->openupval; uv != NULL; uv = uv->u.open.next) {
        work++;
        if (!iswhite(uv))  
          markvalue(g, uv->v);  
      }
    }
  }
  return work;
}