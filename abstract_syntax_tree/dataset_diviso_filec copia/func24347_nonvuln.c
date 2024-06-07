xmlInitPlatformSpecificIo(void)
{
    static int xmlPlatformIoInitialized = 0;
    OSVERSIONINFO osvi;

    if(xmlPlatformIoInitialized)
      return;

    osvi.dwOSVersionInfoSize = sizeof(osvi);

    if(GetVersionEx(&osvi) && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)) {
      xmlWrapStat = xmlWrapStatUtf8;
      xmlWrapOpen = xmlWrapOpenUtf8;
#ifdef HAVE_ZLIB_H
      xmlWrapGzOpen = xmlWrapGzOpenUtf8;
#endif
    } else {
      xmlWrapStat = xmlWrapStatNative;
      xmlWrapOpen = xmlWrapOpenNative;
#ifdef HAVE_ZLIB_H
      xmlWrapGzOpen = gzopen;
#endif
    }

    xmlPlatformIoInitialized = 1;
    return;
}