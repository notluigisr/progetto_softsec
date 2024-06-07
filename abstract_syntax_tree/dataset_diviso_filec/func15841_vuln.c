static int autosieve_createfolder(const char *userid, const struct auth_state *auth_state,
                                  const char *internalname, int createsievefolder)
{
    const char *subf ;
    int r = 0;
    int n;

    
    if (userid == NULL || internalname == NULL)
        return IMAP_MAILBOX_NONEXISTENT;

    syslog(LOG_DEBUG, "STR",
           userid, internalname);

    if (config_getswitch(IMAPOPT_ANYSIEVEFOLDER)) {
        createsievefolder = 1;
    }
    else if ((subf = config_getstring(IMAPOPT_AUTOCREATE_SIEVE_FOLDERS)) != NULL) {
        strarray_t *create = strarray_split(subf, SEP, STRARRAY_TRIM);

        for (n = 0; n < create->count; n++) {
            const char *name = strarray_nth(create, n);
            char *foldername = mboxname_user_mbox(userid, name);

            if (!strcmp(foldername, internalname))
                createsievefolder = 1;

            free(foldername);
            if (createsievefolder) break;
        }

        strarray_free(create);
    }

    
    if (!createsievefolder) return IMAP_MAILBOX_NONEXISTENT;

    
    struct mboxlock *namespacelock = mboxname_usernamespacelock(internalname);

    
    r = mboxlist_lookup(internalname, 0, 0);
    if (r != IMAP_MAILBOX_NONEXISTENT) goto done;

    r = mboxlist_createmailbox(internalname, 0, NULL,
                               1, userid, auth_state, 0, 0, 0, 1, NULL);
    if (r) {
        syslog(LOG_ERR, "STR",
               userid, internalname, error_message(r));
        goto done;
    }

    mboxlist_changesub(internalname, userid, auth_state, 1, 1, 1);
    syslog(LOG_DEBUG, "STR",
           userid, internalname);

done:
    mboxname_release(&namespacelock);
    return r;
}