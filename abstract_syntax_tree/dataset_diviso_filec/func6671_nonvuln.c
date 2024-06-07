static time_t mktimeFromDateOnly(const struct tm *src)
{
    
    struct tm tmp;
    memcpy(&tmp, src, sizeof tmp);

    
    tmp.tm_hour = 0;
    tmp.tm_min  = 0;
    tmp.tm_sec  = 0;
    return mktime(&tmp);
}