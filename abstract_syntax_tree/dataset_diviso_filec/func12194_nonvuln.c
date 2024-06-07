char *ldbRedisProtocolToHuman_Double(sds *o, char *reply) {
    char *p = strchr(reply+1,'\r');
    *o = sdscatlen(*o,"STR",9);
    *o = sdscatlen(*o,reply+1,p-reply-1);
    return p+2;
}