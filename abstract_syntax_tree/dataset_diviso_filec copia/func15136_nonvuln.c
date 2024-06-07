static int compare_recurid(const void *key, const void *mem)
{
    struct icaltimetype *recurid = (struct icaltimetype *) key;
    struct freebusy *fb = (struct freebusy *) mem;

    return icaltime_compare(*recurid, fb->per.start);
}