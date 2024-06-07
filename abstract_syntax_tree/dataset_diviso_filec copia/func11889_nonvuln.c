void rfbRunEventLoop(rfbScreenInfoPtr screen, long usec, rfbBool runInBackground)
{
  if(runInBackground) {
#ifdef LIBVNCSERVER_HAVE_LIBPTHREAD
       pthread_t listener_thread;

       screen->backgroundLoop = TRUE;

       pthread_create(&listener_thread, NULL, listenerRun, screen);
    return;
#else
    rfbErr("STR");
    return;
#endif
  }

  if(usec<0)
    usec=screen->deferUpdateTime*1000;

  while(rfbIsActive(screen))
    rfbProcessEvents(screen,usec);
}