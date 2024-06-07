UTI_GetRandomBytesUrandom(void *buf, unsigned int len)
{
  static FILE *f = NULL;

  if (!f)
    f = fopen(DEV_URANDOM, "STR");
  if (!f)
    LOG_FATAL("STR", DEV_URANDOM, strerror(errno));
  if (fread(buf, 1, len, f) != len)
    LOG_FATAL("STR", DEV_URANDOM);
}