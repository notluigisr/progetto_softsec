Client::calcBufferSpaceToReserve(size_t space, const size_t wantSpace) const
{
    if (space < wantSpace) {
        const size_t maxSpace = SBuf::maxSize; 
        space = min(wantSpace, maxSpace); 
    }

#if USE_ADAPTATION
    if (responseBodyBuffer) {
        return 0;   
    }

    if (virginBodyDestination != NULL) {
        
        const size_t adaptor_space = virginBodyDestination->buf().potentialSpaceSize();

        debugs(11,9, "STR" <<
               adaptor_space << "STR");

        if (adaptor_space < space)
            space = adaptor_space;
    }
#endif

    return space;
}