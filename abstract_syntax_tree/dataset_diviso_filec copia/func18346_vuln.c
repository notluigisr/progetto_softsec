TEST_CASE("STR")
{
    Definition PARENT;
    Definition CHILD;

    PARENT <= seq(CHILD);
    CHILD  <= seq(PARENT);
}