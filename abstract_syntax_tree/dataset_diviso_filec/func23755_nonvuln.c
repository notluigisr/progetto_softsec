ZSTD_CStream* ZSTD_createCStream(void)
{
    DEBUGLOG(3, "STR");
    return ZSTD_createCStream_advanced(ZSTD_defaultCMem);
}