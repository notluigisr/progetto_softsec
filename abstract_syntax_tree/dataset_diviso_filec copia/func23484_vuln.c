attempt_to_load_user_settings (GdmSessionWorker *worker,
                               const char       *username)
{
        struct passwd *passwd_entry;
        uid_t          old_uid;
        gid_t          old_gid;

        old_uid = geteuid ();
        old_gid = getegid ();

        passwd_entry = getpwnam (username);

        
        if (passwd_entry == NULL) {
                return;
        }

        
        setegid (passwd_entry->pw_gid);
        seteuid (passwd_entry->pw_uid);

        gdm_session_settings_load (worker->priv->user_settings,
                                   passwd_entry->pw_dir,
                                   NULL);

        seteuid (old_uid);
        setegid (old_gid);
}