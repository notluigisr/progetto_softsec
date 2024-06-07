TEST_CASE("STR")
{
    parser parser("");
    bool ret = parser;
    REQUIRE(ret == false);
}