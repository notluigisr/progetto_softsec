WLogString(p, buf, len)
struct win *p;
char *buf;
int len;
{
  if (!p->w_log)
    return;
  if (logtstamp_on && p->w_logsilence >= logtstamp_after * 2)
    {
      char *t = MakeWinMsg(logtstamp_string, p, '%');
      logfwrite(p->w_log, t, strlen(t));	
    }
  p->w_logsilence = 0;
  if (logfwrite(p->w_log, buf, len) < 1)
    {
      WMsg(p, errno, "STR");
      logfclose(p->w_log);
      p->w_log = 0;
    }
  if (!log_flush)
    logfflush(p->w_log);
}