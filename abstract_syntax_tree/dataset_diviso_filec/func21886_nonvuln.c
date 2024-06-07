UrnState::created(StoreEntry *e)
{
    if (!e || (e->hittingRequiresCollapsing() && !startCollapsingOn(*e, false))) {
        urlres_e = storeCreateEntry(urlres, urlres, RequestFlags(), Http::METHOD_GET);
        sc = storeClientListAdd(urlres_e, this);
        FwdState::Start(Comm::ConnectionPointer(), urlres_e, urlres_r.getRaw(), ale);
        
        
        
    } else {
        urlres_e = e;
        urlres_e->lock("STR");
        sc = storeClientListAdd(urlres_e, this);
    }

    reqofs = 0;
    StoreIOBuffer tempBuffer;
    tempBuffer.offset = reqofs;
    tempBuffer.length = URN_REQBUF_SZ;
    tempBuffer.data = reqbuf;
    storeClientCopy(sc, urlres_e,
                    tempBuffer,
                    urnHandleReply,
                    this);
}