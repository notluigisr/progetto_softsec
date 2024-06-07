static apr_status_t percentage_parse(const char *value, int *ppercent)
{
    char *endp;
    apr_int64_t n;
    
    n = apr_strtoi64(value, &endp, 10);
    if (errno) {
        return errno;
    }
    if (*endp == '%') {
        if (n < 0 || n >= 100) {
            return APR_BADARG;
        }
        *ppercent = (int)n;
        return APR_SUCCESS;
    }
    return APR_EINVAL;
}