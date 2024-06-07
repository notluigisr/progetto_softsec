crypt_pw_cmp(const char *userpwd, const char *dbpwd)
{
    int rc;
    char *cp;
    struct crypt_data data;
    data.initialized = 0;

    
    cp = crypt_r(userpwd, dbpwd, &data);
    if (cp) {
        rc = slapi_ct_memcmp(dbpwd, cp, strlen(dbpwd));
    } else {
        rc = -1;
    }
    return rc;
}