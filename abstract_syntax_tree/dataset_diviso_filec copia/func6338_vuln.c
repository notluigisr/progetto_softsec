libxlLoggerOpenFile(libxlLogger *logger,
                    int id,
                    const char *name,
                    const char *domain_config)
{
    g_autofree char *path = NULL;
    FILE *logFile = NULL;
    g_autofree char *domidstr = NULL;

    path = g_strdup_printf("STR", logger->logDir, name);
    domidstr = g_strdup_printf("STR", id);

    if (!(logFile = fopen(path, "STR"))) {
        VIR_WARN("STR",
                 path, g_strerror(errno));
        return;
    }
    ignore_value(virHashAddEntry(logger->files, domidstr, logFile));

    
    if (domain_config) {
        fprintf(logFile, "STR", domain_config);
        fflush(logFile);
    }
}