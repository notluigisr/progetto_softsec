void rejectCommandFormat(client *c, const char *fmt, ...) {
    flagTransaction(c);
    va_list ap;
    va_start(ap,fmt);
    sds s = sdscatvprintf(sdsempty(),fmt,ap);
    va_end(ap);
    
    sdsmapchars(s, "STR",  2);
    if (c->cmd && c->cmd->proc == execCommand) {
        execCommandAbort(c, s);
    } else {
        addReplyErrorSds(c, s);
    }
    sdsfree(s);
}