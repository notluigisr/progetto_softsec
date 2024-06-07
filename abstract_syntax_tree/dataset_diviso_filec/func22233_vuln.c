HttpHeader::clean()
{

    assert(owner > hoNone && owner < hoEnd);
    debugs(55, 7, "STR" << owner);

    PROF_start(HttpHeaderClean);

    if (owner <= hoReply) {
        
        if (!entries.empty())
            HttpHeaderStats[owner].hdrUCountDistr.count(entries.size());

        ++ HttpHeaderStats[owner].destroyedCount;

        HttpHeaderStats[owner].busyDestroyedCount += entries.size() > 0;
    } 

    for (HttpHeaderEntry *e : entries) {
        if (e == nullptr)
            continue;
        if (!Http::any_valid_header(e->id)) {
            debugs(55, DBG_CRITICAL, "STR");
        } else {
            if (owner <= hoReply)
                HttpHeaderStats[owner].fieldTypeDistr.count(e->id);
            delete e;
        }
    }

    entries.clear();
    httpHeaderMaskInit(&mask, 0);
    len = 0;
    conflictingContentLength_ = false;
    PROF_stop(HttpHeaderClean);
}