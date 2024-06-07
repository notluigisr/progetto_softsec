TEST_F(ExpressionDateFromStringTest, OptimizesToConstantIfAllInputsAreConstant) {
    auto expCtx = getExpCtx();
    
    auto spec = BSON("STR"
                                               << "STR"));
    auto dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
    ASSERT(dynamic_cast<ExpressionConstant*>(dateExp->optimize().get()));

    Date_t dateVal = Date_t::fromMillisSinceEpoch(1499173797000);
    ASSERT_VALUE_EQ(Value(dateVal), dateExp->evaluate(Document{}));

    
    spec = BSON("STR"
                                          << "STR"
                                          << "STR"
                                          << "STR"));
    dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
    ASSERT(dynamic_cast<ExpressionConstant*>(dateExp->optimize().get()));

    dateVal = Date_t::fromMillisSinceEpoch(1499170197000);
    ASSERT_VALUE_EQ(Value(dateVal), dateExp->evaluate(Document{}));

    
    spec = BSON("STR"
                                          << "STR"));
    dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
    ASSERT_FALSE(dynamic_cast<ExpressionConstant*>(dateExp->optimize().get()));

    
    spec = BSON("STR"
                                          << "STR"
                                          << "STR"
                                          << "STR"));
    dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
    ASSERT_FALSE(dynamic_cast<ExpressionConstant*>(dateExp->optimize().get()));
}