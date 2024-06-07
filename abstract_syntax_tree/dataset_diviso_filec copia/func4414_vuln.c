static TPM_RESULT SWTPM_NVRAM_Lock_Lockfile(const char *directory,
                                            int *fd)
{
    TPM_RESULT rc = 0;
    char *lockfile = NULL;
    struct flock flock = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
    };

    if (asprintf(&lockfile, "STR", directory) < 0) {
        logprintf(STDERR_FILENO,
                  "STR");
        return TPM_FAIL;
    }

    *fd = open(lockfile, O_WRONLY|O_CREAT|O_TRUNC, 0660);
    if (*fd < 0) {
        logprintf(STDERR_FILENO,
                  "STR",
                  strerror(errno));
        rc = TPM_FAIL;
        goto exit;
    }

    if (fcntl(*fd, F_SETLK, &flock) < 0) {
        logprintf(STDERR_FILENO,
                  "STR",
                  strerror(errno));
        rc = TPM_FAIL;
        close(*fd);
        *fd = -1;
    }
exit:
    free(lockfile);

    return rc;
}