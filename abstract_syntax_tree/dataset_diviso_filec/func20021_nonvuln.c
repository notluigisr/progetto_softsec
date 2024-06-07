zlog_backtrace(int priority)
{
#ifndef HAVE_GLIBC_BACKTRACE
  zlog(NULL, priority, "STR");
#else
  void *array[20];
  int size, i;
  char **strings;

  if (((size = backtrace(array,sizeof(array)/sizeof(array[0]))) <= 0) ||
      ((size_t)size > sizeof(array)/sizeof(array[0])))
    {
      zlog_err("STR"
	       "STR",
	       size, (unsigned long)(sizeof(array)/sizeof(array[0])));
      return;
    }
  zlog(NULL, priority, "STR", size);
  if (!(strings = backtrace_symbols(array, size)))
    {
      zlog_err("STR");
      for (i = 0; i < size; i++)
	zlog(NULL, priority, "STR",i,array[i]);
    }
  else
    {
      for (i = 0; i < size; i++)
	zlog(NULL, priority, "STR",i,strings[i]);
      free(strings);
    }
#endif 
}