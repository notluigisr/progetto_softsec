prepareLogWithRequestDetails(HttpRequest * request, AccessLogEntry::Pointer &aLogEntry)
{
    assert(request);
    assert(aLogEntry != NULL);

    if (Config.onoff.log_mime_hdrs) {
        MemBuf mb;
        mb.init();
        request->header.packInto(&mb);
        
        aLogEntry->headers.adapted_request = xstrdup(mb.buf);

        
        if (aLogEntry->request) {
            mb.reset();
            aLogEntry->request->header.packInto(&mb);
            aLogEntry->headers.request = xstrdup(mb.buf);
        }

#if USE_ADAPTATION
        const Adaptation::History::Pointer ah = request->adaptLogHistory();
        if (ah != NULL) {
            mb.reset();
            ah->lastMeta.packInto(&mb);
            aLogEntry->adapt.last_meta = xstrdup(mb.buf);
        }
#endif

        mb.clean();
    }

#if ICAP_CLIENT
    const Adaptation::Icap::History::Pointer ih = request->icapHistory();
    if (ih != NULL)
        ih->processingTime(aLogEntry->icap.processingTime);
#endif

    aLogEntry->http.method = request->method;
    aLogEntry->http.version = request->http_ver;
    aLogEntry->hier = request->hier;
    aLogEntry->cache.extuser = request->extacl_user.termedBuf();

    
    
    
    if (aLogEntry->request) {
        aLogEntry->request->dnsWait = request->dnsWait;
        aLogEntry->request->error = request->error;
    }
}