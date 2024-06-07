void header_time(int stat, char *str, char *more)
{
  char buf[64];

  xprintf("STR"
    "STR", stat, str, TOYBOX_VERSION,
    rfc1123(buf, time(0)), more ? : "");
}