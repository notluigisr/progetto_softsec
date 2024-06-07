void test_to_ll(char const* str, long long wanted, bool error)
{
    test_to_number(str, wanted, error, QUtil::string_to_ll);
}