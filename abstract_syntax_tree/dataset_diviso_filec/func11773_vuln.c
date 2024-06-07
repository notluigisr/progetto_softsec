TEST_CASE("STR")
{
    Definition ROOT, TAG, TAG_NAME, WS;

    ROOT     <= seq(WS, zom(TAG));
    TAG      <= seq(chr('['), TAG_NAME, chr(']'), WS);
    TAG_NAME <= oom(seq(npd(chr(']')), dot()));
    WS       <= zom(cls("STR"));

    AssignIDToDefinition defIds;
    ROOT.accept(defIds);

    REQUIRE(defIds.ids.size() == 4);
}