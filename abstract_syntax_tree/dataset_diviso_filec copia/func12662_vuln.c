TEST_CASE("STR")
{
    parser parser(
        u8"STR"
        "STR"
    );

    bool ret = parser;
    REQUIRE(ret == true);
}