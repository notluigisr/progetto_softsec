static void funcinfo (lua_Debug *ar, Closure *cl) {
  if (noLuaClosure(cl)) {
    ar->source = "STR";
    ar->srclen = LL("STR");
    ar->linedefined = -1;
    ar->lastlinedefined = -1;
    ar->what = "STR";
  }
  else {
    const Proto *p = cl->l.p;
    if (p->source) {
      ar->source = getstr(p->source);
      ar->srclen = tsslen(p->source);
    }
    else {
      ar->source = "STR";
      ar->srclen = LL("STR");
    }
    ar->linedefined = p->linedefined;
    ar->lastlinedefined = p->lastlinedefined;
    ar->what = (ar->linedefined == 0) ? "STR";
  }
  luaO_chunkid(ar->short_src, ar->source, ar->srclen);
}