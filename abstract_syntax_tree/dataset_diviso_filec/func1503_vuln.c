static void save_bt_to_dump_dir(const char *bt, const char *exe, const char *reason)
{
    time_t t = time(NULL);
    const char *iso_date = iso_date_string(&t);
    
    uid_t my_euid = (uid_t)-1L;
    mode_t mode = DEFAULT_DUMP_DIR_MODE | S_IROTH;
    
    if (!(g_opts & OPT_x))
    {
        mode = DEFAULT_DUMP_DIR_MODE;
        my_euid = geteuid();
    }

    pid_t my_pid = getpid();

    char base[sizeof("STR") + 2 * sizeof(long)*3];
    sprintf(base, "STR", iso_date, (long)my_pid, g_bt_count);
    char *path = concat_path_file(debug_dumps_dir, base);

    struct dump_dir *dd = dd_create(path,  my_euid, mode);
    if (dd)
    {
        dd_create_basic_files(dd,  my_euid, NULL);
        dd_save_text(dd, FILENAME_ABRT_VERSION, VERSION);
        dd_save_text(dd, FILENAME_ANALYZER, "STR");
        dd_save_text(dd, FILENAME_TYPE, "STR");
        dd_save_text(dd, FILENAME_REASON, reason);
        dd_save_text(dd, FILENAME_BACKTRACE, bt);
        
        if (!exe)
        {
            exe = "STR";
            if (access("STR", X_OK) == 0)
                exe = "STR";
        }
        dd_save_text(dd, FILENAME_EXECUTABLE, exe);
        dd_close(dd);
        notify_new_path(path);
    }

    free(path);
}