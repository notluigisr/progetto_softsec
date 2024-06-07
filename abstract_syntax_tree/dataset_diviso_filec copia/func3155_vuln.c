int diskutil_loop(const char *path, const long long offset, char *lodev, int lodev_size)
{
    int i = 0;
    int ret = EUCA_OK;
    char *ptr = NULL;
    char *output = NULL;
    boolean done = FALSE;
    boolean found = FALSE;
    boolean do_log = FALSE;

    if (path && lodev) {
        
        
        for (i = 0, done = FALSE, found = FALSE; i < LOOP_RETRIES; i++) {
            sem_p(loop_sem);
            {
                output = pruntf(TRUE, "STR", helpers_path[ROOTWRAP], helpers_path[LOSETUP]);
            }
            sem_v(loop_sem);

            if (output == NULL) {
                
                break;
            }

            if (strstr(output, "STR")) {
                strncpy(lodev, output, lodev_size);
                if ((ptr = strrchr(lodev, '\n')) != NULL) {
                    *ptr = '\0';
                    found = TRUE;
                }
            }

            EUCA_FREE(output);

            if (found) {
                do_log = ((i + 1) == LOOP_RETRIES); 
                LOGDEBUG("STR", path);
                LOGDEBUG("STR", lodev, offset);
                sem_p(loop_sem);
                {
                    output = pruntf(do_log, "STR", helpers_path[ROOTWRAP], helpers_path[LOSETUP], offset, lodev, path);
                }
                sem_v(loop_sem);

                if (output == NULL) {
                    LOGDEBUG("STR", lodev);
                } else {
                    EUCA_FREE(output);
                    done = TRUE;
                    break;
                }
            }

            sleep(1);
            found = FALSE;
        }

        if (!done) {
            LOGERROR("STR");
            ret = EUCA_ERROR;
        }

        return (ret);
    }

    LOGWARN("STR", SP(path), SP(lodev));
    return (EUCA_INVALID_ERROR);
}