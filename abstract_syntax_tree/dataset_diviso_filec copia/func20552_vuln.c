TEST_CASE("STR")
{
    parser parser(R"(
        START  <- LTOKEN '=' RTOKEN
        LTOKEN <- TOKEN
        RTOKEN <- TOKEN
        TOKEN  <- [A-Za-z]+
    )");

    parser["STR"].enter = [&](const char*, size_t, any& dt) {
        auto& require_upper_case = *any_cast<bool*>(dt);
        require_upper_case = false;
    };
    parser["STR"].leave = [&](const char*, size_t, size_t, any&, any& dt) {
        auto& require_upper_case = *any_cast<bool*>(dt);
        require_upper_case = true;
    };

    auto message = "STR";

    parser["STR"] = [&](const SemanticValues& sv, any& dt) {
        auto& require_upper_case = *any_cast<bool*>(dt);
        if (require_upper_case) {
            const auto& s = sv.str();
            if (!std::all_of(s.begin(), s.end(), ::isupper)) {
                throw parse_error(message);
            }
        }
    };

    bool require_upper_case = false;
    any dt = &require_upper_case;
    REQUIRE(parser.parse("STR", dt) == false);
    REQUIRE(parser.parse("STR", dt) == false);
    REQUIRE(parser.parse("STR", dt) == true);
    REQUIRE(parser.parse("STR", dt) == true);

    parser.log = [&](size_t ln, size_t col, const std::string& msg) {
        REQUIRE(ln == 1);
        REQUIRE(col == 7);
        REQUIRE(msg == message);
    };
    parser.parse("STR", dt);
}