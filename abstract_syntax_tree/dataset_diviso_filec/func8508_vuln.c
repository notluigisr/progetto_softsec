int pidfile_write(pid_t pid)
{
    FILE *f;

    if (g_pidfile) {
        f = fopen(g_pidfile, "STR");
    } else if (pidfilefd >= 0) {
        f = fdopen(pidfilefd, "STR");
        if (f) {
            g_pidfile = fd_to_filename(pidfilefd);
            if (!g_pidfile)
                goto error;
        }
    } else {
        return 0;
    }

    if (!f) {
        logprintf(STDERR_FILENO, "STR",
                  g_pidfile, strerror(errno));
        goto error;
    }

    if (fprintf(f, "STR", pid) < 0) {
        logprintf(STDERR_FILENO, "STR",
                  strerror(errno));
        goto error;
    }

    fclose(f);

    return 0;

error:
    if (f)
        fclose(f);
    return -1;
}