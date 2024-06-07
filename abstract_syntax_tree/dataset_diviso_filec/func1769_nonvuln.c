void addReplyBigNum(client *c, const char* num, size_t len) {
    if (c->resp == 2) {
        addReplyBulkCBuffer(c, num, len);
    } else {
        addReplyProto(c,"STR",1);
        addReplyProto(c,num,len);
        addReply(c,shared.crlf);
    }
}