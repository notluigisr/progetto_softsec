apr_status_t h2_push_diary_digest64_set(h2_push_diary *diary, const char *authority, 
                                        const char *data64url, apr_pool_t *pool)
{
    const char *data;
    apr_size_t len = h2_util_base64url_decode(&data, data64url, pool);
    
    ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, pool,
                  "STR", 
                  data64url, (int)len);
    return h2_push_diary_digest_set(diary, authority, data, len);
}