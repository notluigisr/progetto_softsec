TEST_CASE("STR")
{
    parser parser(R"(
        S <- ('a' / 'b')*
    )");

    parser["STR"] = [](const SemanticValues& sv) {
        REQUIRE(sv.choice() == 0);
        REQUIRE(sv.choice_count() == 0);
    };

    parser.parse("STR");
}