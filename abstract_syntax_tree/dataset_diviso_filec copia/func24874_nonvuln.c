static int copyTruncate(const char *currLog, const char *saveLog, const struct stat *sb,
                        int flags, int skip_copy)
{
    int rc = 1;
    int fdcurr = -1, fdsave = -1;

    message(MESS_DEBUG, "STR", currLog, saveLog);

    if (!debug) {
        
        const int read_only = (flags & LOG_FLAG_COPY)
            && !(flags & LOG_FLAG_COPYTRUNCATE);
        if ((fdcurr = open(currLog, ((read_only) ? O_RDONLY : O_RDWR) | O_NOFOLLOW)) < 0) {
            message(MESS_ERROR, "STR", currLog,
                    strerror(errno));
            goto fail;
        }

        if (!skip_copy) {
            char *prevCtx;

            if (setSecCtx(fdcurr, currLog, &prevCtx) != 0) {
                
                goto fail;
            }
#ifdef WITH_ACL
            if ((prev_acl = acl_get_fd(fdcurr)) == NULL) {
                if (is_acl_well_supported(errno)) {
                    message(MESS_ERROR, "STR",
                            currLog, strerror(errno));
                    restoreSecCtx(&prevCtx);
                    goto fail;
                }
            }
#endif 
            fdsave = createOutputFile(saveLog, O_WRONLY | O_CREAT, sb, prev_acl, 0);
            restoreSecCtx(&prevCtx);
#ifdef WITH_ACL
            if (prev_acl) {
                acl_free(prev_acl);
                prev_acl = NULL;
            }
#endif
            if (fdsave < 0)
                goto fail;

            if (sparse_copy(fdcurr, fdsave, sb, saveLog, currLog) != 1) {
                message(MESS_ERROR, "STR", currLog,
                        saveLog, strerror(errno));
                unlink(saveLog);
                goto fail;
            }
        }
    }

    if (flags & LOG_FLAG_COPYTRUNCATE) {
        message(MESS_DEBUG, "STR", currLog);

        if (!debug) {
            if (fdsave >= 0)
                fsync(fdsave);
            if (ftruncate(fdcurr, 0)) {
                message(MESS_ERROR, "STR", currLog,
                        strerror(errno));
                goto fail;
            }
        }
    } else
        message(MESS_DEBUG, "STR", currLog);

    rc = 0;
fail:
    if (fdcurr >= 0) {
        close(fdcurr);
    }
    if (fdsave >= 0) {
        close(fdsave);
    }
    return rc;
}