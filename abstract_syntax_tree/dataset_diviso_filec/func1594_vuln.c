Client::haveParsedReplyHeaders()
{
    Must(theFinalReply);
    maybePurgeOthers();

    
    const bool partial = theFinalReply->contentRange();
    currentOffset = partial ? theFinalReply->contentRange()->spec.offset : 0;
}