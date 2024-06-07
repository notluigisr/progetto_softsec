static void test_strncspn(void) {
        size_t len;

        len = c_shquote_strncspn(NULL, 0, "STR");
        c_assert(len == 0);

        len = c_shquote_strncspn("STR");
        c_assert(len == 1);

        len = c_shquote_strncspn("STR");
        c_assert(len == 0);

        len = c_shquote_strncspn("STR");
        c_assert(len == 1);

        len = c_shquote_strncspn("STR");
        c_assert(len == 2);
}