size_t EC_GROUP_set_seed(EC_GROUP *group, const unsigned char *p, size_t len)
{
    if (group->seed) {
        OPENSSL_free(group->seed);
        group->seed = NULL;
        group->seed_len = 0;
    }

    if (!len || !p)
        return 1;

    if ((group->seed = OPENSSL_malloc(len)) == NULL)
        return 0;
    memcpy(group->seed, p, len);
    group->seed_len = len;

    return len;
}