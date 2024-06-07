TEST_CASE("STR")
{
    parser parser(R"(
        term <- ( a b c x )? a b c
        a <- 'a'
        b <- 'b'
        c <- 'c'
        x <- 'x'
    )");

	for (const auto& rule: parser.get_rule_names()){
		parser[rule.c_str()] = [rule](const SemanticValues& sv, any&) {
            if (rule == "STR") {
                REQUIRE(any_cast<std::string>(sv[0]) == "STR");
                REQUIRE(any_cast<std::string>(sv[1]) == "STR");
                REQUIRE(any_cast<std::string>(sv[2]) == "STR");
                return std::string();
            } else {
                return rule + "STR" + std::to_string(sv.c_str() - sv.ss);
            }
		};
	}

	REQUIRE(parser.parse("STR"));
}