UTI_ZeroTimespec(struct timespec *ts)
{
  ts->tv_sec = 0;
  ts->tv_nsec = 0;
}