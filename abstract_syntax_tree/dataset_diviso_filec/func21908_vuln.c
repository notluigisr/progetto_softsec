check_user_file (const char *filename,
                 uid_t       user,
                 gssize      max_file_size,
                 gboolean    relax_group,
                 gboolean    relax_other)
{
        struct stat fileinfo;

        if (max_file_size < 0) {
                max_file_size = G_MAXSIZE;
        }

        
        if (stat (filename, &fileinfo) < 0) {
                return FALSE;
        }

        
        if (G_UNLIKELY (!S_ISREG (fileinfo.st_mode))) {
                return FALSE;
        }

        
        if (G_UNLIKELY (fileinfo.st_uid != user)) {
                return FALSE;
        }

        
        if (G_UNLIKELY ((fileinfo.st_mode & S_IWGRP) == S_IWGRP && !relax_group)) {
                return FALSE;
        }

        
        if (G_UNLIKELY ((fileinfo.st_mode & S_IWOTH) == S_IWOTH && !relax_other)) {
                return FALSE;
        }

        
        if (G_UNLIKELY (fileinfo.st_size > max_file_size)) {
                return FALSE;
        }

        return TRUE;
}