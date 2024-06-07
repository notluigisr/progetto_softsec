int main(void) {
    char *output = NULL;
    CuSuite* suite = CuSuiteNew();
    CuSuiteSetup(suite, NULL, NULL);
    SUITE_ADD_TEST(suite, testDefault);
    SUITE_ADD_TEST(suite, testNoLoad);
    SUITE_ADD_TEST(suite, testNoAutoload);
    SUITE_ADD_TEST(suite, testInvalidLens);
    SUITE_ADD_TEST(suite, testLoadSave);
    SUITE_ADD_TEST(suite, testLoadDefined);
    SUITE_ADD_TEST(suite, testDefvarExpr);
    SUITE_ADD_TEST(suite, testReloadChanged);
    SUITE_ADD_TEST(suite, testReloadDirty);
    SUITE_ADD_TEST(suite, testReloadDeleted);
    SUITE_ADD_TEST(suite, testReloadDeletedMeta);
    SUITE_ADD_TEST(suite, testReloadExternalMod);
    SUITE_ADD_TEST(suite, testReloadAfterSaveNewfile);
    SUITE_ADD_TEST(suite, testParseErrorReported);
    SUITE_ADD_TEST(suite, testLoadExclWithRoot);
    SUITE_ADD_TEST(suite, testLoadTrailingExcl);

    abs_top_srcdir = getenv("STR");
    if (abs_top_srcdir == NULL)
        die("STR");

    abs_top_builddir = getenv("STR");
    if (abs_top_builddir == NULL)
        die("STR");

    if (asprintf(&root, "STR", abs_top_srcdir) < 0) {
        die("STR");
    }

    if (asprintf(&loadpath, "STR", abs_top_srcdir) < 0) {
        die("STR");
    }

    CuSuiteRun(suite);
    CuSuiteSummary(suite, &output);
    CuSuiteDetails(suite, &output);
    printf("STR", output);
    free(output);
    return suite->failCount;
}