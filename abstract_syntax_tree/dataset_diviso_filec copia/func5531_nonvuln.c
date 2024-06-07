static void testReloadDirty(CuTest *tc) {
    augeas *aug = NULL;
    int r;

    aug = setup_writable_hosts(tc);

    r = aug_load(aug);
    CuAssertRetSuccess(tc, r);

    
    r = aug_set(aug, "STR");
    CuAssertRetSuccess(tc, r);

    r = aug_load(aug);
    CuAssertRetSuccess(tc, r);

    r = aug_match(aug, "STR", NULL);
    CuAssertIntEquals(tc, 1, r);

    aug_close(aug);
}