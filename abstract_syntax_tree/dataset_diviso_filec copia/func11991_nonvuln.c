void xsetidCommand(client *c) {
    robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
    if (o == NULL || checkType(c,o,OBJ_STREAM)) return;

    stream *s = o->ptr;
    streamID id;
    if (streamParseStrictIDOrReply(c,c->argv[2],&id,0) != C_OK) return;

    
    if (s->length > 0) {
        streamID maxid;
        streamLastValidID(s,&maxid);

        if (streamCompareID(&id,&maxid) < 0) {
            addReplyError(c,"STR"
                            "STR");
            return;
        }
    }
    s->last_id = id;
    addReply(c,shared.ok);
    server.dirty++;
    notifyKeyspaceEvent(NOTIFY_STREAM,"STR",c->argv[1],c->db->id);
}