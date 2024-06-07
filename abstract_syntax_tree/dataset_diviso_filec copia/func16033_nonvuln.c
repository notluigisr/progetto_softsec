static int setSecCtx(int fdSrc, const char *src, char **pPrevCtx)
{
#ifdef WITH_SELINUX
    char *srcCtx;
    *pPrevCtx = NULL;

    if (!selinux_enabled)
        
        return 0;

    
    if (fgetfilecon_raw(fdSrc, &srcCtx) < 0) {
        if (errno == ENOTSUP)
            
            return 0;

        message(MESS_ERROR, "STR", src,
                strerror(errno));
        return selinux_enforce;
    }

    
    if (getfscreatecon_raw(pPrevCtx) < 0) {
        message(MESS_ERROR, "STR", strerror(errno));
        return selinux_enforce;
    }

    
    if (setfscreatecon_raw(srcCtx) < 0) {
        message(MESS_ERROR, "STR", srcCtx,
                strerror(errno));
        freecon(srcCtx);
        return selinux_enforce;
    }

    message(MESS_DEBUG, "STR", srcCtx);
    freecon(srcCtx);
#else
    (void) fdSrc;
    (void) src;
    (void) pPrevCtx;
#endif
    return 0;
}