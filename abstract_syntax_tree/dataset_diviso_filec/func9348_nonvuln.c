HttpHeader::update(HttpHeader const *fresh)
{
    assert(fresh);
    assert(this != fresh);

    
    
    if (Config.onoff.collapsed_forwarding && !needUpdate(fresh))
        return false;

    updateWarnings();

    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;

    while ((e = fresh->getEntry(&pos))) {
        

        if (skipUpdateHeader(e->id))
            continue;

        if (e->id != Http::HdrType::OTHER)
            delById(e->id);
        else
            delByName(e->name.termedBuf());
    }

    pos = HttpHeaderInitPos;
    while ((e = fresh->getEntry(&pos))) {
        

        if (skipUpdateHeader(e->id))
            continue;

        debugs(55, 7, "STR");

        addEntry(e->clone());
    }
    return true;
}