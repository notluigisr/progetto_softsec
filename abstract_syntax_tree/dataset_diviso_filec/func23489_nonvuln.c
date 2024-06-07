cmsIOHANDLER* CMSEXPORT cmsOpenIOhandlerFromMem(cmsContext ContextID, void *Buffer, cmsUInt32Number size, const char* AccessMode)
{
    cmsIOHANDLER* iohandler = NULL;
    FILEMEM* fm = NULL;

	_cmsAssert(AccessMode != NULL);

    iohandler = (cmsIOHANDLER*) _cmsMallocZero(ContextID, sizeof(cmsIOHANDLER));
    if (iohandler == NULL) return NULL;

    switch (*AccessMode) {

    case 'r':
        fm = (FILEMEM*) _cmsMallocZero(ContextID, sizeof(FILEMEM));
        if (fm == NULL) goto Error;

        if (Buffer == NULL) {
            cmsSignalError(ContextID, cmsERROR_READ, "STR");
            goto Error;
        }

        fm ->Block = (cmsUInt8Number*) _cmsMalloc(ContextID, size);
        if (fm ->Block == NULL) {

            _cmsFree(ContextID, fm);
            _cmsFree(ContextID, iohandler);
            cmsSignalError(ContextID, cmsERROR_READ, "STR", size);
            return NULL;
        }


        memmove(fm->Block, Buffer, size);
        fm ->FreeBlockOnClose = TRUE;
        fm ->Size    = size;
        fm ->Pointer = 0;
        iohandler -> ReportedSize = size;
        break;

    case 'w':
        fm = (FILEMEM*) _cmsMallocZero(ContextID, sizeof(FILEMEM));
        if (fm == NULL) goto Error;

        fm ->Block = (cmsUInt8Number*) Buffer;
        fm ->FreeBlockOnClose = FALSE;
        fm ->Size    = size;
        fm ->Pointer = 0;
        iohandler -> ReportedSize = 0;
        break;

    default:
        cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "STR", *AccessMode);
        return NULL;
    }

    iohandler ->ContextID = ContextID;
    iohandler ->stream  = (void*) fm;
    iohandler ->UsedSpace = 0;
    iohandler ->PhysicalFile[0] = 0;

    iohandler ->Read    = MemoryRead;
    iohandler ->Seek    = MemorySeek;
    iohandler ->Close   = MemoryClose;
    iohandler ->Tell    = MemoryTell;
    iohandler ->Write   = MemoryWrite;

    return iohandler;

Error:
    if (fm) _cmsFree(ContextID, fm);
    if (iohandler) _cmsFree(ContextID, iohandler);
    return NULL;
}