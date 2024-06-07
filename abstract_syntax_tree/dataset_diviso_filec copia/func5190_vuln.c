ImagingNew(const char* mode, int xsize, int ysize)
{
    int bytes;
    Imaging im;

    if (strlen(mode) == 1) {
        if (mode[0] == 'F' || mode[0] == 'I')
            bytes = 4;
        else
            bytes = 1;
    } else
        bytes = strlen(mode); 

    if ((int64_t) xsize * (int64_t) ysize <= THRESHOLD / bytes) {
        im = ImagingNewBlock(mode, xsize, ysize);
        if (im)
            return im;
        
        ImagingError_Clear();
    }

    return ImagingNewArray(mode, xsize, ysize);
}