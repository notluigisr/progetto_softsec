cmsIOHANDLER* CMSEXPORT cmsOpenIOhandlerFromFile(cmsContext ContextID, const char* FileName, const char* AccessMode)
{
    cmsIOHANDLER* iohandler = NULL;
    FILE* fm = NULL;

    iohandler = (cmsIOHANDLER*) _cmsMallocZero(ContextID, sizeof(cmsIOHANDLER));
    if (iohandler == NULL) return NULL;

    switch (*AccessMode) {

    case 'r':
        fm = fopen(FileName, "STR");
        if (fm == NULL) {
            _cmsFree(ContextID, iohandler);
             cmsSignalError(ContextID, cmsERROR_FILE, "STR", FileName);
            return NULL;
        }
        iohandler -> ReportedSize = cmsfilelength(fm);
        break;

    case 'w':
        fm = fopen(FileName, "STR");
        if (fm == NULL) {
            _cmsFree(ContextID, iohandler);
             cmsSignalError(ContextID, cmsERROR_FILE, "STR", FileName);
            return NULL;
        }
        iohandler -> ReportedSize = 0;
        break;

    default:
        _cmsFree(ContextID, iohandler);
         cmsSignalError(ContextID, cmsERROR_FILE, "STR", *AccessMode);
        return NULL;
    }

    iohandler ->ContextID = ContextID;
    iohandler ->stream = (void*) fm;
    iohandler ->UsedSpace = 0;

    
    if (FileName != NULL)  {

        strncpy(iohandler -> PhysicalFile, FileName, sizeof(iohandler -> PhysicalFile)-1);
        iohandler -> PhysicalFile[sizeof(iohandler -> PhysicalFile)-1] = 0;
    }

    iohandler ->Read    = FileRead;
    iohandler ->Seek    = FileSeek;
    iohandler ->Close   = FileClose;
    iohandler ->Tell    = FileTell;
    iohandler ->Write   = FileWrite;

    return iohandler;
}