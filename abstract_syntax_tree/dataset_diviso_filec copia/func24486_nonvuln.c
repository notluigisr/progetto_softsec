crypt_pw_cmp(const char *userpwd, const char *dbpwd)
{
    int rc = -1;
    char *cp = NULL;
    size_t dbpwd_len = strlen(dbpwd);
    struct crypt_data data;
    data.initialized = 0;

    
    if (dbpwd_len >= 3) {
        
        cp = crypt_r(userpwd, dbpwd, &data);
    }
    
    if (cp && dbpwd_len == strlen(cp)) {
        rc = slapi_ct_memcmp(dbpwd, cp, dbpwd_len);
    } else {
        rc = -1;
    }
    return rc;
}