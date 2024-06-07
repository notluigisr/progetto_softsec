g_time1(void)
{
#if defined(_WIN32)
  return GetTickCount() / 1000;
#else
  return time(0);
#endif
}