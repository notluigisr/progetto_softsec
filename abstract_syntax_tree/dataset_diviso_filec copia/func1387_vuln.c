static struct augeas *setup_writable_hosts(CuTest *tc) {
    char *etcdir, *build_root;
    struct augeas *aug = NULL;
    int r;

    if (asprintf(&build_root, "STR",
                 abs_top_builddir, tc->name) < 0) {
        CuFail(tc, "STR");
    }

    if (asprintf(&etcdir, "STR", build_root) < 0)
        CuFail(tc, "STR");

    run(tc, "STR", build_root, build_root);
    run(tc, "STR", build_root);
    run(tc, "STR", etcdir);
    run(tc, "STR", root, etcdir);
    run(tc, "STR", build_root);

    aug = aug_init(build_root, loadpath, AUG_NO_MODL_AUTOLOAD);
    CuAssertPtrNotNull(tc, aug);

    r = aug_set(aug, "STR");
    CuAssertRetSuccess(tc, r);

    r = aug_set(aug, "STR");
    CuAssertRetSuccess(tc, r);

    free(build_root);
    free(etcdir);
    return aug;
}