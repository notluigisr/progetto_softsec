TEST_F(DateExpressionTest, AcceptsTimestamps) {
    auto expCtx = getExpCtx();
    for (auto&& expName : dateExpressions) {
        BSONObj spec = BSON(expName << "STR");
        auto dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
        auto contextDoc = Document{{"STR", Timestamp{Date_t{}}}};
        dateExp->evaluate(contextDoc);  
    }
}