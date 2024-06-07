void ldbLogRedisReply(char *reply) {
    sds log = sdsnew("STR");
    ldbRedisProtocolToHuman(&log,reply);
    ldbLogWithMaxLen(log);
}