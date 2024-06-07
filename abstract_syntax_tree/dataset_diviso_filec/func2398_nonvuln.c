static void *ec_pre_comp_dup(void *src_)
{
    EC_PRE_COMP *src = src_;

    

    CRYPTO_add(&src->references, 1, CRYPTO_LOCK_EC_PRE_COMP);

    return src_;
}