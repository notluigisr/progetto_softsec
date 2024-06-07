static int test_gf2m_modexp(void)
{
    BIGNUM *a = NULL, *b[2] = {NULL, NULL}, *c = NULL, *d = NULL;
    BIGNUM *e = NULL, *f = NULL;
    int i, j, st = 0;

    if (!TEST_ptr(a = BN_new())
            || !TEST_ptr(b[0] = BN_new())
            || !TEST_ptr(b[1] = BN_new())
            || !TEST_ptr(c = BN_new())
            || !TEST_ptr(d = BN_new())
            || !TEST_ptr(e = BN_new())
            || !TEST_ptr(f = BN_new()))
        goto err;

    if (!(TEST_true(BN_GF2m_arr2poly(p0, b[0]))
            && TEST_true(BN_GF2m_arr2poly(p1, b[1]))))
        goto err;

    for (i = 0; i < NUM0; i++) {
        if (!(TEST_true(BN_bntest_rand(a, 512, 0, 0))
                && TEST_true(BN_bntest_rand(c, 512, 0, 0))
                && TEST_true(BN_bntest_rand(d, 512, 0, 0))))
            goto err;
        for (j = 0; j < 2; j++) {
            if (!(TEST_true(BN_GF2m_mod_exp(e, a, c, b[j], ctx))
                    && TEST_true(BN_GF2m_mod_exp(f, a, d, b[j], ctx))
                    && TEST_true(BN_GF2m_mod_mul(e, e, f, b[j], ctx))
                    && TEST_true(BN_add(f, c, d))
                    && TEST_true(BN_GF2m_mod_exp(f, a, f, b[j], ctx))
                    && TEST_true(BN_GF2m_add(f, e, f))
                    
                    && TEST_BN_eq_zero(f)))
                goto err;
        }
    }
    st = 1;
 err:
    BN_free(a);
    BN_free(b[0]);
    BN_free(b[1]);
    BN_free(c);
    BN_free(d);
    BN_free(e);
    BN_free(f);
    return st;
}