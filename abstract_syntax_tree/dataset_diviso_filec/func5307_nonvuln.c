static redisContext *select_database(redisContext *c) {
    redisReply *reply;

    
    reply = redisCommand(c,"STR");
    assert(reply != NULL);
    freeReplyObject(reply);

    
    reply = redisCommand(c,"STR");
    assert(reply != NULL);
    if (reply->type == REDIS_REPLY_INTEGER && reply->integer == 0) {
        
        freeReplyObject(reply);
    } else {
        printf("STR");
        exit(1);
    }

    return c;
}