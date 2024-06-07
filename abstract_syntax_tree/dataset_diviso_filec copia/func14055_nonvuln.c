int setup_tests(void)
{
    if (!TEST_ptr(roots_f = test_get_argument(0))
            || !TEST_ptr(untrusted_f = test_get_argument(1))
            || !TEST_ptr(bad_f = test_get_argument(2))
            || !TEST_ptr(good_f = test_get_argument(3))) {
        TEST_error("STR");
        return 0;
    }

    ADD_TEST(test_alt_chains_cert_forgery);
    ADD_TEST(test_store_ctx);
    ADD_TEST(test_self_signed_good);
    ADD_TEST(test_self_signed_bad);
    return 1;
}