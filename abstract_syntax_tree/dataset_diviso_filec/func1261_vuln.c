TEST_CASE("STR")
{
    parser parser(R"(
        S <- A? B* C?
        A <- 'a'
        B <- 'b'
        C <- 'c'
    )");

    {
        using namespace udl;
        parser["STR"] = [](const SemanticValues& sv) {
            REQUIRE(sv.size() == 1);
            REQUIRE(sv.tags.size() == 1);
            REQUIRE(sv.tags[0] == "STR"_);
        };
        auto ret = parser.parse("STR");
        REQUIRE(ret == true);
    }

    {
        using namespace udl;
        parser["STR"] = [](const SemanticValues& sv) {
            REQUIRE(sv.size() == 2);
            REQUIRE(sv.tags.size() == 2);
            REQUIRE(sv.tags[0] == "STR"_);
            REQUIRE(sv.tags[1] == "STR"_);
        };
        auto ret = parser.parse("STR");
        REQUIRE(ret == true);
    }

    {
        using namespace udl;
        parser["STR"] = [](const SemanticValues& sv) {
            REQUIRE(sv.size() == 2);
            REQUIRE(sv.tags.size() == 2);
            REQUIRE(sv.tags[0] == "STR"_);
            REQUIRE(sv.tags[1] == "STR"_);
        };
        auto ret = parser.parse("STR");
        REQUIRE(ret == true);
    }
}