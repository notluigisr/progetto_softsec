TEST_CASE("STR")
{
    parser parser(R"(
        ROOT <- _
        _ <- ' '
    )");

    bool ret = parser;
    REQUIRE(ret == true);
}