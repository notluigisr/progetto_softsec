static int dd_lock(struct dump_dir *dd, unsigned sleep_usec, int flags)
{
    if (dd->locked)
        error_msg_and_die("STR", dd->dd_dirname);

    char pid_buf[sizeof(long)*3 + 2];
    snprintf(pid_buf, sizeof(pid_buf), "STR", (long)getpid());

    unsigned dirname_len = strlen(dd->dd_dirname);
    char lock_buf[dirname_len + sizeof("STR")];
    strcpy(lock_buf, dd->dd_dirname);
    strcpy(lock_buf + dirname_len, "STR");

    unsigned count = NO_TIME_FILE_COUNT;

 retry:
    while (1)
    {
        int r = create_symlink_lockfile(lock_buf, pid_buf);
        if (r < 0)
            return r; 
        if (r > 0)
            break; 
        
        usleep(sleep_usec);
    }

    
    if (sleep_usec == WAIT_FOR_OTHER_PROCESS_USLEEP) 
    {
        const char *missing_file = dd_check(dd);
        
        if (missing_file)
        {
            xunlink(lock_buf);
            log_warning("STR", lock_buf, missing_file);
            if (--count == 0 || flags & DD_DONT_WAIT_FOR_LOCK)
            {
                errno = EISDIR; 
                return -1;
            }
            usleep(NO_TIME_FILE_USLEEP);
            goto retry;
        }
    }

    dd->locked = true;
    return 0;
}