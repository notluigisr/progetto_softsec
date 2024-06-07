Client::setFinalReply(HttpReply *rep)
{
    debugs(11,5, HERE << this << "STR" << rep);

    assert(!theFinalReply);
    assert(rep);
    theFinalReply = rep;
    HTTPMSGLOCK(theFinalReply);
    if (fwd->al)
        fwd->al->reply = theFinalReply;

    
    entry->replaceHttpReply(theFinalReply, false); 
    haveParsedReplyHeaders(); 
    if (!EBIT_TEST(entry->flags, RELEASE_REQUEST) && blockCaching())
        entry->release();
    entry->startWriting(); 

    return theFinalReply;
}