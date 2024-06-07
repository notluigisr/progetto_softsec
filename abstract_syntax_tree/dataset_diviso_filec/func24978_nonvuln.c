HttpHeader::removeHopByHopEntries()
{
    removeConnectionHeaderEntries();

    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;
    int headers_deleted = 0;
    while ((e = getEntry(&pos))) {
        Http::HdrType id = e->id;
        if (Http::HeaderLookupTable.lookup(id).hopbyhop) {
            delAt(pos, headers_deleted);
            CBIT_CLR(mask, id);
        }
    }
}