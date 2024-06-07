cmsUInt32Number NULLRead(cmsIOHANDLER* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count)
{
    FILENULL* ResData = (FILENULL*) iohandler ->stream;

    cmsUInt32Number len = size * count;
    ResData -> Pointer += len;
    return count;

    cmsUNUSED_PARAMETER(Buffer);
}