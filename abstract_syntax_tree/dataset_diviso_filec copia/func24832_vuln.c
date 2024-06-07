TEST_CASE("STR")
{
    parser parser(R"(
        S <- 'a' / 'b'
    )");

    parser["STR"] = [](const SemanticValues& sv) {
        REQUIRE(sv.choice() == 1);
        REQUIRE(sv.choice_count() == 2);
    };

    parser.parse("STR");
}