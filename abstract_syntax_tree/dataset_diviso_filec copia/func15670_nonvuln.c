UTI_IsZeroTimespec(struct timespec *ts)
{
  return !ts->tv_sec && !ts->tv_nsec;
}