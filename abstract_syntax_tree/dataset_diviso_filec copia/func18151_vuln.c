TEST_CASE("STR")
{
    parser parser(R"(
        ROOT      <-  _ ('[' TAG_NAME ']' _)*
        TAG_NAME  <-  (!']' .)+
        _         <-  [ \t]*
    )");

    std::vector<std::string> tags;

    parser["STR"] = [&](const SemanticValues& sv) {
        tags.push_back(sv.str());
    };

    auto ret = parser.parse("STR");

    REQUIRE(ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "STR");
    REQUIRE(tags[1] == "STR");
    REQUIRE(tags[2] == "STR");
}