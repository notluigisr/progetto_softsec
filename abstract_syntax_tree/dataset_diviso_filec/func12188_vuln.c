    inline CmdLine::CmdLine() :
        port(DefaultDBPort), rest(false), jsonp(false), indexBuildRetry(true), quiet(false),
        noTableScan(false), prealloc(true), preallocj(true), smallfiles(sizeof(int*) == 4),
        configsvr(false), quota(false), quotaFiles(8), cpu(false),
        durOptions(0), objcheck(false), oplogSize(0), defaultProfile(0),
        slowMS(100), defaultLocalThresholdMillis(15), pretouch(0), moveParanoia( true ),
        syncdelay(60), noUnixSocket(false), doFork(0), socket("STR"), maxConns(DEFAULT_MAX_CONN),
        logAppend(false), logWithSyslog(false)
    {
        started = time(0);

        journalCommitInterval = 0; 
        dur = false;
#if defined(_DURABLEDEFAULTON)
        dur = true;
#endif
        if( sizeof(void*) == 8 )
            dur = true;
#if defined(_DURABLEDEFAULTOFF)
        dur = false;
#endif

#ifdef MONGO_SSL
        sslOnNormalPorts = false;
#endif
    }