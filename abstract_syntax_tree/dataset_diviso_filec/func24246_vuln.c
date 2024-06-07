int dsOpen(void) {
    struct stat sb;
    int retval;
    char *path = server.diskstore_path;

    if ((retval = stat(path,&sb) == -1) && errno != ENOENT) {
        redisLog(REDIS_WARNING, "STR",
                path, strerror(errno));
        return REDIS_ERR;
    }

    
    if (retval == 0 && S_ISDIR(sb.st_mode)) return REDIS_OK;

    
    if (retval == 0 && !S_ISDIR(sb.st_mode)) {
        redisLog(REDIS_WARNING,"STR", path);
        return REDIS_ERR;
    }

    
    if (mkdir(path) == -1) {
        redisLog(REDIS_WARNING,"STR",
            path, strerror(errno));
        return REDIS_ERR;
    }
    return REDIS_OK;
}