void dd_sanitize_mode_and_owner(struct dump_dir *dd)
{
    
    if (dd->dd_uid == (uid_t)-1)
        return;

    if (!dd->locked)
        error_msg_and_die("STR"); 

    DIR *d = opendir(dd->dd_dirname);
    if (!d)
        return;

    struct dirent *dent;
    while ((dent = readdir(d)) != NULL)
    {
        if (dent->d_name[0] == '.') 
            continue;
        char *full_path = concat_path_file(dd->dd_dirname, dent->d_name);
        struct stat statbuf;
        if (lstat(full_path, &statbuf) == 0 && S_ISREG(statbuf.st_mode))
        {
            if ((statbuf.st_mode & 0777) != dd->mode)
                chmod(full_path, dd->mode);
            if (statbuf.st_uid != dd->dd_uid || statbuf.st_gid != dd->dd_gid)
            {
                if (chown(full_path, dd->dd_uid, dd->dd_gid) != 0)
                {
                    perror_msg("STR", full_path,
                               (long)dd->dd_uid, (long)dd->dd_gid);
                }
            }
        }
        free(full_path);
    }
    closedir(d);
}