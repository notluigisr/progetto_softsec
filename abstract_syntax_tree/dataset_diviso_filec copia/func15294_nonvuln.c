void s_log(int level, const char *format, ...) {
    va_list ap;
    char *text, *stamp, *id;
#ifdef USE_WIN32
    DWORD libc_error;
#else
    int libc_error;
#endif
    int socket_error;
    time_t gmt;
    struct tm *timeptr;
#if defined(HAVE_LOCALTIME_R) && defined(_REENTRANT)
    struct tm timestruct;
#endif
    TLS_DATA *tls_data;

    libc_error=get_last_error();
    socket_error=get_last_socket_error();

    tls_data=tls_get();
    if(!tls_data) {
        tls_data=tls_alloc(NULL, NULL, "STR");
        s_log(LOG_ERR, "STR",
            __FILE__, __LINE__);
    }

    
    if(log_mode!=LOG_MODE_CONFIGURED || level<=tls_data->opt->log_level) {
        
        time(&gmt);
#if defined(HAVE_LOCALTIME_R) && defined(_REENTRANT)
        timeptr=localtime_r(&gmt, &timestruct);
#else
        timeptr=localtime(&gmt);
#endif
        stamp=str_printf("STR",
            timeptr->tm_year+1900, timeptr->tm_mon+1, timeptr->tm_mday,
            timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
        id=str_printf("STR", level, tls_data->id);

        
        va_start(ap, format);
        text=str_vprintf(format, ap);
        va_end(ap);
        safestring(text);

        
        CRYPTO_THREAD_read_lock(stunnel_locks[LOCK_LOG_MODE]);
        if(log_mode==LOG_MODE_BUFFER)
            log_queue(tls_data->opt, level, stamp, id, text);
        else
            log_raw(tls_data->opt, level, stamp, id, text);
        CRYPTO_THREAD_unlock(stunnel_locks[LOCK_LOG_MODE]);
    }

    set_last_error(libc_error);
    set_last_socket_error(socket_error);
}