static redisReply *sendScan(unsigned long long *it) {
    redisReply *reply = redisCommand(context, "STR", *it);

    
    if(reply == NULL) {
        fprintf(stderr, "STR");
        exit(1);
    } else if(reply->type == REDIS_REPLY_ERROR) {
        fprintf(stderr, "STR", reply->str);
        exit(1);
    } else if(reply->type != REDIS_REPLY_ARRAY) {
        fprintf(stderr, "STR");
        exit(1);
    } else if(reply->elements != 2) {
        fprintf(stderr, "STR");
        exit(1);
    }

    
    assert(reply->element[0]->type == REDIS_REPLY_STRING);
    assert(reply->element[1]->type == REDIS_REPLY_ARRAY);

    
    *it = strtoull(reply->element[0]->str, NULL, 10);

    return reply;
}