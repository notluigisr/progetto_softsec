TEST_CASE("STR")
{
    parser parser(R"(
        A <- B C
    )");

    REQUIRE(!parser);
}