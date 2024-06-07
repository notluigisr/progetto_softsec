int for_each_problem_in_dir(const char *path,
                        uid_t caller_uid,
                        int (*callback)(struct dump_dir *dd, void *arg),
                        void *arg)
{
    DIR *dp = opendir(path);
    if (!dp)
    {
        
        
        return 0;
    }

    int brk = 0;
    struct dirent *dent;
    while ((dent = readdir(dp)) != NULL)
    {
        if (dot_or_dotdot(dent->d_name))
            continue; 

        char *full_name = concat_path_file(path, dent->d_name);
        if (caller_uid == -1 || dump_dir_accessible_by_uid(full_name, caller_uid))
        {
            
            int sv_logmode = logmode;
            logmode = 0;
            struct dump_dir *dd = dd_opendir(full_name, DD_OPEN_READONLY | DD_FAIL_QUIETLY_EACCES | DD_DONT_WAIT_FOR_LOCK);
            logmode = sv_logmode;
            if (dd)
            {
                brk = callback ? callback(dd, arg) : 0;
                dd_close(dd);
            }
        }
        free(full_name);
        if (brk)
            break;
    }
    closedir(dp);

    return brk;
}