TEST_CASE("STR")
{
    std::vector<std::string> tags;

    Definition ROOT, TAG, TAG_NAME, WS;
    ROOT     <= seq(WS, zom(TAG));
    TAG      <= seq(chr('['), TAG_NAME, chr(']'), WS);
    TAG_NAME <= oom(seq(npd(chr(']')), dot())), [&](const SemanticValues& sv) { tags.push_back(sv.str()); };
    WS       <= zom(cls("STR"));

    auto r = ROOT.parse("STR");

    REQUIRE(r.ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "STR");
    REQUIRE(tags[1] == "STR");
    REQUIRE(tags[2] == "STR");
}