int prepareForShutdown() {
    redisLog(REDIS_WARNING,"STR");
    
    if (server.bgsavechildpid != -1) {
        redisLog(REDIS_WARNING,"STR");
        kill(server.bgsavechildpid,SIGKILL);
        rdbRemoveTempFile(server.bgsavechildpid);
    }
    if (server.appendonly) {
        
        aof_fsync(server.appendfd);
        if (server.vm_enabled) unlink(server.vm_swap_file);
    } else if (server.saveparamslen > 0) {
        
        if (rdbSave(server.dbfilename) != REDIS_OK) {
            
            redisLog(REDIS_WARNING,"STR");
            return REDIS_ERR;
        }
    } else {
        redisLog(REDIS_WARNING,"STR");
    }
    if (server.daemonize) unlink(server.pidfile);
    redisLog(REDIS_WARNING,"STR");
    return REDIS_OK;
}