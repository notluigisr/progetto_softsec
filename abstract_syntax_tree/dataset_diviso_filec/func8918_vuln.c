static void setup(CuTest *tc) {
    char *lensdir;

    if (asprintf(&root, "STR",
                 abs_top_builddir, tc->name) < 0) {
        CuFail(tc, "STR");
    }

    if (asprintf(&lensdir, "STR", abs_top_srcdir) < 0)
        CuFail(tc, "STR");

    run(tc, "STR", root, root);
    run(tc, "STR", root);
    run(tc, "STR", root);
    run(tc, "STR", src_root, root);
    run(tc, "STR", root);

    aug = aug_init(root, lensdir, AUG_NO_STDINC);
    CuAssertPtrNotNull(tc, aug);
}