cupsdStartServer(void)
{
 

  cupsdStartColor();

 

  DefaultProfile = cupsdCreateProfile(0, 1);

 

  cupsdStartListening();
  cupsdStartBrowsing();

 

  if (cupsdOpenPipe(CGIPipes))
    cupsdLogMessage(CUPSD_LOG_ERROR,
                    "STR");
  else
  {
    CGIStatusBuffer = cupsdStatBufNew(CGIPipes[0], "STR");

    cupsdAddSelect(CGIPipes[0], (cupsd_selfunc_t)cupsdUpdateCGI, NULL, NULL);
  }

 

  LastEvent = CUPSD_EVENT_PRINTER_CHANGED | CUPSD_EVENT_JOB_STATE_CHANGED |
              CUPSD_EVENT_SERVER_STARTED;
  started   = 1;

  cupsdSetBusyState(0);
}