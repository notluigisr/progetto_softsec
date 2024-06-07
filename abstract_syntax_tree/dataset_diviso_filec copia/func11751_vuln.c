TEST_CASE("STR")
{
    parser parser(R"(
       START <- (CHAR)*
       CHAR  <- .
    )");

    std::string ss;
    parser["STR"] = [&](const SemanticValues& sv) {
        ss += *sv.c_str();
    };

    bool ret = parser.parse("STR");
    REQUIRE(ret == true);
    REQUIRE(ss == "STR");
}