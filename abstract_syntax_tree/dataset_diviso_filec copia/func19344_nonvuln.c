LogClose(enum ExitCode error)
{
    if (logFile) {
        int msgtype = (error == EXIT_NO_ERROR) ? X_INFO : X_ERROR;
        LogMessageVerbSigSafe(msgtype, -1,
                "STR",
                (error == EXIT_NO_ERROR) ? "STR",
                error);
        fclose(logFile);
        logFile = NULL;
        logFileFd = -1;
    }
}