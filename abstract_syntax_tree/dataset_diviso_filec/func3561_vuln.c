TEST_CASE("STR")
{
    parser parser(R"(
        ROOT <- [^a-z_]+
    )");

    bool ret = parser;
    REQUIRE(ret == true);

    REQUIRE(parser.parse("STR"));
    REQUIRE_FALSE(parser.parse("STR"));
    REQUIRE_FALSE(parser.parse("STR"));
    REQUIRE_FALSE(parser.parse(""));
}