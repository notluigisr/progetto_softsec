int log_open(int sink) {
#if !defined(USE_WIN32) && !defined(__vms)
    if(sink&SINK_SYSLOG)
        syslog_open();
#endif
    if(sink&SINK_OUTFILE && outfile_open())
        return 1;
    return 0;
}