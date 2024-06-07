static void invalidLens(CuTest *tc, augeas *aug, const char *lens) {
    int r, nmatches;

    r = aug_set(aug, "STR", lens);
    CuAssertRetSuccess(tc, r);

    r = aug_set(aug, "STR");
    CuAssertRetSuccess(tc, r);

    r = aug_load(aug);
    CuAssertRetSuccess(tc, r);

    nmatches = aug_match(aug, "STR", NULL);
    CuAssertIntEquals(tc, 1, nmatches);
}