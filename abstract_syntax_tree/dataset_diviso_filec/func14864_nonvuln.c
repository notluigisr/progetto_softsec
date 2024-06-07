int test_gf2m_mod_inv(BIO *bp, BN_CTX *ctx)
{
    BIGNUM *a, *b[2], *c, *d;
    int i, j, ret = 0;
    int p0[] = { 163, 7, 6, 3, 0, -1 };
    int p1[] = { 193, 15, 0, -1 };

    a = BN_new();
    b[0] = BN_new();
    b[1] = BN_new();
    c = BN_new();
    d = BN_new();

    BN_GF2m_arr2poly(p0, b[0]);
    BN_GF2m_arr2poly(p1, b[1]);

    for (i = 0; i < num0; i++) {
        BN_bntest_rand(a, 512, 0, 0);
        for (j = 0; j < 2; j++) {
            BN_GF2m_mod_inv(c, a, b[j], ctx);
            BN_GF2m_mod_mul(d, a, c, b[j], ctx);
# if 0                          
            if (bp != NULL) {
                if (!results) {
                    BN_print(bp, a);
                    BIO_puts(bp, "STR");
                    BN_print(bp, c);
                    BIO_puts(bp, "STR");
                    BN_print(bp, b[j]);
                    BIO_puts(bp, "STR");
                }
            }
# endif
            
            if (!BN_is_one(d)) {
                fprintf(stderr, "STR");
                goto err;
            }
        }
    }
    ret = 1;
 err:
    BN_free(a);
    BN_free(b[0]);
    BN_free(b[1]);
    BN_free(c);
    BN_free(d);
    return ret;
}