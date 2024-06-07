int diskutil_ddzero(const char *path, const long long sectors, boolean zero_fill)
{
    char *output = NULL;
    long long count = 1;
    long long seek = sectors - 1;

    if (path) {
        if (zero_fill) {
            count = sectors;
            seek = 0;
        }

        output = pruntf(TRUE, "STR", helpers_path[ROOTWRAP], helpers_path[DD], path, seek, count);
        if (!output) {
            LOGERROR("STR", path);
            return (EUCA_ERROR);
        }

        EUCA_FREE(output);
        return (EUCA_OK);
    }

    LOGWARN("STR", SP(path));
    return (EUCA_INVALID_ERROR);
}