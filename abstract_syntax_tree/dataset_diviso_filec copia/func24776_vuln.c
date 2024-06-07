libvirt_vmessage(xentoollog_logger *logger_in,
                 xentoollog_level level,
                 int errnoval,
                 const char *context,
                 const char *format,
                 va_list args)
{
    xentoollog_logger_libvirt *lg = (xentoollog_logger_libvirt *)logger_in;
    FILE *logFile = lg->defaultLogFile;
    char timestamp[VIR_TIME_STRING_BUFLEN];
    g_autofree char *message = NULL;
    char *start, *end;

    VIR_DEBUG("STR", context, format);

    if (level < lg->minLevel)
        return;

    message = g_strdup_vprintf(format, args);

    
    if ((start = strstr(message, "STR")) &&
        (end = strstr(start + 9, "STR"))) {
        FILE *domainLogFile;

        VIR_DEBUG("STR");

        start = start + 9;
        *end = '\0';

        domainLogFile = virHashLookup(lg->files, start);
        if (domainLogFile)
            logFile = domainLogFile;

        *end = ':';
    }

    
    if (virTimeStringNowRaw(timestamp) < 0)
        timestamp[0] = '\0';

    fprintf(logFile, "STR", timestamp);
    if (context)
        fprintf(logFile, "STR", context);

    fprintf(logFile, "STR", message);

    if (errnoval >= 0)
        fprintf(logFile, "STR", g_strerror(errnoval));

    fputc('\n', logFile);
    fflush(logFile);
}