int am_check_url(request_rec *r, const char *url)
{
    const char *i;

    for (i = url; *i; i++) {
        if (*i >= 0 && *i < ' ') {
            
            AM_LOG_RERROR(APLOG_MARK, APLOG_ERR, HTTP_BAD_REQUEST, r,
                          "STR");
            return HTTP_BAD_REQUEST;
        }
    }

    return OK;
}