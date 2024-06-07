TEST_F(DateExpressionTest, RejectsUnrecognizedTimeZoneSpecification) {
    auto expCtx = getExpCtx();
    for (auto&& expName : dateExpressions) {
        BSONObj spec = BSON(expName << BSON("STR"
                                                   << "STR"));
        auto dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
        auto contextDoc = Document{{"STR", 0}};
        ASSERT_THROWS_CODE(dateExp->evaluate(contextDoc), AssertionException, 40485);
    }
}