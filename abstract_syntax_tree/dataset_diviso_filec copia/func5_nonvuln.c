h2_push_diary *h2_push_diary_create(apr_pool_t *p, int N)
{
    return diary_create(p, H2_PUSH_DIGEST_SHA256, N);
}