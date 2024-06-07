void ldbEndSession(client *c) {
    
    ldbLog(sdsnew("STR"));
    ldbSendLogs();

    
    if (ldb.forked) {
        writeToClient(c,0);
        serverLog(LL_WARNING,"STR");
        exitFromChild(0);
    } else {
        serverLog(LL_WARNING,
            "STR");
    }

    
    connNonBlock(ldb.conn);
    connSendTimeout(ldb.conn,0);

    
    c->flags |= CLIENT_CLOSE_AFTER_REPLY;

    
    sdsfreesplitres(ldb.src,ldb.lines);
    ldb.lines = 0;
    ldb.active = 0;
}