static RAND_DRBG *drbg_setup(RAND_DRBG *parent)
{
    RAND_DRBG *drbg;

    drbg = RAND_DRBG_secure_new(rand_drbg_type, rand_drbg_flags, parent);
    if (drbg == NULL)
        return NULL;

    
    if (parent == NULL && rand_drbg_enable_locking(drbg) == 0)
        goto err;

    
    tsan_store(&drbg->reseed_prop_counter, 1);

    
    (void)RAND_DRBG_instantiate(drbg,
                                (const unsigned char *) ossl_pers_string,
                                sizeof(ossl_pers_string) - 1);
    return drbg;

err:
    RAND_DRBG_free(drbg);
    return NULL;
}