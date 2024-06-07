static void LogPathInfo(const PathInfo *path_info)
{
  register const PathInfo
    *p;

  (void) LogMagickEvent(DrawEvent,GetMagickModule(),"STR");
  for (p=path_info; p->code != EndCode; p++)
    (void) LogMagickEvent(DrawEvent,GetMagickModule(),
      "STR",p->point.x,p->point.y,p->code == GhostlineCode ?
      "STR" :
      p->code == MoveToCode ? "STR" :
      "STR");
  (void) LogMagickEvent(DrawEvent,GetMagickModule(),"STR");
}