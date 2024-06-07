TEST_CASE("STR")
{
    parser parser(R"(
        EXPRESSION       <-  _ TERM (TERM_OPERATOR TERM)*
        TERM             <-  FACTOR (FACTOR_OPERATOR FACTOR)*
        FACTOR           <-  NUMBER / '(' _ EXPRESSION ')' _
        TERM_OPERATOR    <-  < [-+] > _
        FACTOR_OPERATOR  <-  < [/*] > _
        NUMBER           <-  < [0-9]+ > _
        _                <-  [ \t\r\n]*
    )");

    REQUIRE(parser["STR"].is_token() == false);
    REQUIRE(parser["STR"].is_token() == false);
    REQUIRE(parser["STR"].is_token() == true);
    REQUIRE(parser["STR"].is_token() == true);
    REQUIRE(parser["STR"].is_token() == true);
}