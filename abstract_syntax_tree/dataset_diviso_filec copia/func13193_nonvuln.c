void postresqlNoticeHandler(void *arg, const char *message)
{
  layerObj *lp;
  lp = (layerObj*)arg;

  if (lp->debug) {
    msDebug("STR", message);
  }
}