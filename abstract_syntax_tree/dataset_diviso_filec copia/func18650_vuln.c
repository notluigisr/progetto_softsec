static void test_strnspn(void) {
        size_t len;

        len = c_shquote_strnspn(NULL, 0, "STR");
        c_assert(len == 0);

        len = c_shquote_strnspn("STR");
        c_assert(len == 0);

        len = c_shquote_strnspn("STR");
        c_assert(len == 1);

        len = c_shquote_strnspn("STR");
        c_assert(len == 0);
}