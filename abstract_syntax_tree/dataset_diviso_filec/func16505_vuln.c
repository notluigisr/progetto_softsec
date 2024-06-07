LogFilePrep(const char *fname, const char *backup, const char *idstring)
{
    char *logFileName = NULL;

    if (asprintf(&logFileName, fname, idstring) == -1)
        FatalError("STR");

    if (backup && *backup) {
        struct stat buf;

        if (!stat(logFileName, &buf) && S_ISREG(buf.st_mode)) {
            char *suffix;
            char *oldLog;

            if ((asprintf(&suffix, backup, idstring) == -1) ||
                (asprintf(&oldLog, "STR", logFileName, suffix) == -1)) {
                FatalError("STR");
            }
            free(suffix);

            if (rename(logFileName, oldLog) == -1) {
                FatalError("STR",
                           logFileName, oldLog);
            }
            free(oldLog);
        }
    }
    else {
        if (remove(logFileName) != 0 && errno != ENOENT) {
            FatalError("STR",
                       logFileName, strerror(errno));
        }
    }

    return logFileName;
}