_lookup_passwd_info (const char *username,
                     uid_t      *uidp,
                     gid_t      *gidp,
                     char      **homep,
                     char      **shellp)
{
        gboolean       ret;
        struct passwd *passwd_entry;
        struct passwd  passwd_buffer;
        char          *aux_buffer;
        long           required_aux_buffer_size;
        gsize          aux_buffer_size;

        ret = FALSE;
        aux_buffer = NULL;
        aux_buffer_size = 0;

        required_aux_buffer_size = sysconf (_SC_GETPW_R_SIZE_MAX);

        if (required_aux_buffer_size < 0) {
                aux_buffer_size = GDM_PASSWD_AUXILLARY_BUFFER_SIZE;
        } else {
                aux_buffer_size = (gsize) required_aux_buffer_size;
        }

        aux_buffer = g_slice_alloc0 (aux_buffer_size);

        
        passwd_entry = NULL;
#ifdef HAVE_POSIX_GETPWNAM_R
        errno = getpwnam_r (username,
                            &passwd_buffer,
                            aux_buffer,
                            (size_t) aux_buffer_size,
                            &passwd_entry);
#else
        passwd_entry = getpwnam_r (username,
                                   &passwd_buffer,
                                   aux_buffer,
                                   (size_t) aux_buffer_size);
        errno = 0;
#endif 

        if (errno != 0) {
                g_warning ("STR", g_strerror (errno));
                goto out;
        }

        if (passwd_entry == NULL) {
                goto out;
        }

        if (uidp != NULL) {
                *uidp = passwd_entry->pw_uid;
        }
        if (gidp != NULL) {
                *gidp = passwd_entry->pw_gid;
        }
        if (homep != NULL) {
                *homep = g_strdup (passwd_entry->pw_dir);
        }
        if (shellp != NULL) {
                *shellp = g_strdup (passwd_entry->pw_shell);
        }
        ret = TRUE;
 out:
        if (aux_buffer != NULL) {
                g_assert (aux_buffer_size > 0);
                g_slice_free1 (aux_buffer_size, aux_buffer);
        }

        return ret;
}