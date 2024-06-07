void geoposCommand(client *c) {
    int j;

    
    robj *zobj = lookupKeyRead(c->db, c->argv[1]);
    if (zobj && checkType(c, zobj, OBJ_ZSET)) return;

    
    addReplyArrayLen(c,c->argc-2);
    for (j = 2; j < c->argc; j++) {
        double score;
        if (!zobj || zsetScore(zobj, c->argv[j]->ptr, &score) == C_ERR) {
            addReplyNullArray(c);
        } else {
            
            double xy[2];
            if (!decodeGeohash(score,xy)) {
                addReplyNullArray(c);
                continue;
            }
            addReplyArrayLen(c,2);
            addReplyHumanLongDouble(c,xy[0]);
            addReplyHumanLongDouble(c,xy[1]);
        }
    }
}