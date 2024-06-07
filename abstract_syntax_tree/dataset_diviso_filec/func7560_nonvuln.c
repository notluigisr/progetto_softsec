static void test_memslot_invalid_addresses(void)
{
    g_test_trap_subprocess("STR", 0, 0);
    g_test_trap_assert_stderr("STR");

    g_test_trap_subprocess("STR", 0, 0);
    g_test_trap_assert_stderr("STR");
}