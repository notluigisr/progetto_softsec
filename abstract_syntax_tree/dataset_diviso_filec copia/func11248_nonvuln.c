void streamPropagateXCLAIM(client *c, robj *key, streamCG *group, robj *groupname, robj *id, streamNACK *nack) {
    
    robj *argv[14];
    argv[0] = createStringObject("STR",6);
    argv[1] = key;
    argv[2] = groupname;
    argv[3] = createStringObject(nack->consumer->name,sdslen(nack->consumer->name));
    argv[4] = createStringObjectFromLongLong(0);
    argv[5] = id;
    argv[6] = createStringObject("STR",4);
    argv[7] = createStringObjectFromLongLong(nack->delivery_time);
    argv[8] = createStringObject("STR",10);
    argv[9] = createStringObjectFromLongLong(nack->delivery_count);
    argv[10] = createStringObject("STR",5);
    argv[11] = createStringObject("STR",6);
    argv[12] = createStringObject("STR",6);
    argv[13] = createObjectFromStreamID(&group->last_id);

    
    propagate(server.xclaimCommand,c->db->id,argv,14,PROPAGATE_AOF|PROPAGATE_REPL);
    decrRefCount(argv[0]);
    decrRefCount(argv[3]);
    decrRefCount(argv[4]);
    decrRefCount(argv[6]);
    decrRefCount(argv[7]);
    decrRefCount(argv[8]);
    decrRefCount(argv[9]);
    decrRefCount(argv[10]);
    decrRefCount(argv[11]);
    decrRefCount(argv[12]);
    decrRefCount(argv[13]);
}