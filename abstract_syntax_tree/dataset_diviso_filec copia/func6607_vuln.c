int diskutil_unloop(const char *lodev)
{
    int i = 0;
    int ret = EUCA_OK;
    int retried = 0;
    char *output = NULL;
    boolean do_log = FALSE;

    if (lodev) {
        LOGDEBUG("STR", lodev);

        
        
        for (i = 0; i < LOOP_RETRIES; i++) {
            do_log = ((i + 1) == LOOP_RETRIES); 
            sem_p(loop_sem);
            {
                output = pruntf(do_log, "STR", helpers_path[ROOTWRAP], helpers_path[LOSETUP], lodev);
            }
            sem_v(loop_sem);

            if (!output) {
                ret = EUCA_ERROR;
            } else {
                ret = EUCA_OK;
                EUCA_FREE(output);
                break;
            }

            LOGDEBUG("STR", lodev);
            retried++;
            sleep(1);
        }

        if (ret == EUCA_ERROR) {
            LOGWARN("STR");
        } else if (retried) {
            LOGINFO("STR", lodev, retried);
        }

        return (ret);
    }

    LOGWARN("STR", SP(lodev));
    return (EUCA_INVALID_ERROR);
}