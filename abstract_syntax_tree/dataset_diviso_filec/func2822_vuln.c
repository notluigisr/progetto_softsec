int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);

    if (getenv("STR")) {
        debug = TRUE;
        vnc_util_set_debug(TRUE);
    }

#if GLIB_CHECK_VERSION(2, 22, 0)
    g_test_add_func("STR", test_validation_rre);
    g_test_add_func("STR", test_validation_copyrect);
    g_test_add_func("STR", test_validation_hextile);
    g_test_add_func("STR", test_validation_unexpected_cmap);
#endif

    return g_test_run();
}