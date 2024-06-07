ClientHttpRequest::mRangeCLen()
{
    int64_t clen = 0;
    MemBuf mb;

    assert(memObject());

    mb.init();
    HttpHdrRange::iterator pos = request->range->begin();

    while (pos != request->range->end()) {
        
        mb.reset();
        clientPackRangeHdr(&storeEntry()->mem().freshestReply(),
                           *pos, range_iter.boundary, &mb);
        clen += mb.size;

        
        clen += (*pos)->length;

        debugs(33, 6, "STR" << clen);
        ++pos;
    }

    
    mb.reset();

    clientPackTermBound(range_iter.boundary, &mb);

    clen += mb.size;

    mb.clean();

    return clen;
}