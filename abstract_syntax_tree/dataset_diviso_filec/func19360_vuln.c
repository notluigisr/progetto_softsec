TEST_CASE("STR")
{
    parser parser(R"(
        A <- ''
        A <- ''
    )");

    REQUIRE(!parser);
}