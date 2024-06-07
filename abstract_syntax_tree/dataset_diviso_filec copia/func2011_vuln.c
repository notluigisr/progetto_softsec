TEST_CASE("STR")
{
    parser pg(R"(
        ROOT  <- _ TOKEN*
        TOKEN <- '[' < (!']' .)+ > ']' _
        _     <- [ \t\r\n]*
    )");


    std::vector<std::string> tags;

    pg["STR"] = [&](const SemanticValues& sv) {
        tags.push_back(sv.token());
    };

    auto ret = pg.parse("STR");

    REQUIRE(ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "STR");
    REQUIRE(tags[1] == "STR");
    REQUIRE(tags[2] == "STR");
}