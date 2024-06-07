static void atomic2gen (lua_State *L, global_State *g) {
  
  sweep2old(L, &g->allgc);
  
  g->reallyold = g->old = g->survival = g->allgc;

  
  sweep2old(L, &g->finobj);
  g->finobjrold = g->finobjold = g->finobjsur = g->finobj;

  sweep2old(L, &g->tobefnz);

  g->gckind = KGC_GEN;
  g->lastatomic = 0;
  g->GCestimate = gettotalbytes(g);  
  finishgencycle(L, g);
}