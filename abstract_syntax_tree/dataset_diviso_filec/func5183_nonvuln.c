http_set_timeout(int    fd,		
                 double timeout)	
{
#ifdef _WIN32
  DWORD tv = (DWORD)(timeout * 1000);
				      

  setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, CUPS_SOCAST &tv, sizeof(tv));
  setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, CUPS_SOCAST &tv, sizeof(tv));

#else
  struct timeval tv;			

  tv.tv_sec  = (int)timeout;
  tv.tv_usec = (int)(1000000 * fmod(timeout, 1.0));

  setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, CUPS_SOCAST &tv, sizeof(tv));
  setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, CUPS_SOCAST &tv, sizeof(tv));
#endif 
}