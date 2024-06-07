int rand_pool_add_end(RAND_POOL *pool, size_t len, size_t entropy)
{
    if (len > pool->max_len - pool->len) {
        RANDerr(RAND_F_RAND_POOL_ADD_END, RAND_R_RANDOM_POOL_OVERFLOW);
        return 0;
    }

    if (len > 0) {
        pool->len += len;
        pool->entropy += entropy;
    }

    return 1;
}