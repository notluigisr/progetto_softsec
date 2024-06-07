  void DefaultEnv::Initialize()
  {
    sLog           = new Log();
    SetUpLog();

    sEnv           = new DefaultEnv();
    sForkHandler   = new ForkHandler();
    sFileTimer     = new FileTimer();
    sPlugInManager = new PlugInManager();

    sPlugInManager->ProcessEnvironmentSettings();
    sForkHandler->RegisterFileTimer( sFileTimer );

    
    
    
    
    
#ifdef __APPLE__
    char *errBuff = new char[1024];

    const char *libs[] =
    {
      "STR",
      "STR",
      "STR",
      "STR",
      "STR",
      "STR",
      "STR",
      "STR",
      0
    };

    for( int i = 0; libs[i]; ++i )
    {
      sLog->Debug( UtilityMsg, "STR", libs[i] );
      bool ok = XrdOucPreload( libs[i], errBuff, 1024 );
      if( !ok )
        sLog->Error( UtilityMsg, "STR", libs[i], errBuff );
    }
    delete [] errBuff;
#endif
  }