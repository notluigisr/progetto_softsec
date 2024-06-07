int diskutil_dd2(const char *in, const char *out, const int bs, const long long count, const long long seek, const long long skip)
{
    char *output = NULL;

    if (in && out) {
        LOGINFO("STR", in);
        LOGINFO("STR", out);
        LOGINFO("STR", count, bs, seek, skip);
        output =
            pruntf(TRUE, "STR", helpers_path[ROOTWRAP], helpers_path[DD], in, out, bs, count, seek, skip);
        if (!output) {
            LOGERROR("STR", in);
            LOGERROR("STR", out);
            return (EUCA_ERROR);
        }

        EUCA_FREE(output);
        return (EUCA_OK);
    }

    LOGWARN("STR", SP(in), SP(out));
    return (EUCA_INVALID_ERROR);
}