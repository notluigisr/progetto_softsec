xmlIOErrMemory(const char *extra)
{
    __xmlSimpleError(XML_FROM_IO, XML_ERR_NO_MEMORY, NULL, NULL, extra);
}