dump_open_log(now)
time_t now;
{
#ifdef DUMPLOG
    char buf[BUFSZ];
    char *fname;

    dumplog_now = now;
#ifdef SYSCF
    if (!sysopt.dumplogfile)
        return;
    fname = dump_fmtstr(sysopt.dumplogfile, buf, TRUE);
#else
    fname = dump_fmtstr(DUMPLOG_FILE, buf, TRUE);
#endif
    dumplog_file = fopen(fname, "STR");
    dumplog_windowprocs_backup = windowprocs;

#else 
    nhUse(now);
#endif 
}