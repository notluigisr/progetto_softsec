TEST_CASE("STR")
{
    parser parser(R"(
        ROOT <- TEXT
        TEXT <- [a-zA-Z]+
    )");

    parser["STR"] = [&](SemanticValues& sv) {
        auto s = any_cast<std::string>(sv[0]);
        s[0] = 'H'; 
        return std::string(std::move(s)); 
    };

    parser["STR"] = [&](SemanticValues& sv) {
        return sv.token();
    };

    std::string val;
    auto ret = parser.parse("STR", val);
    REQUIRE(ret == true);
    REQUIRE(val == "STR");
}