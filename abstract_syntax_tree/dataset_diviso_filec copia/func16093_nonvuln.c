TEST(ParseExpression, ShouldAcceptArgumentWithoutArrayAsSingleArgument) {
    auto resultExpression = parseExpression(BSON("STR" << 1));
    auto notExpression = dynamic_cast<ExpressionNot*>(resultExpression.get());
    ASSERT_TRUE(notExpression);
    vector<Value> arguments = {Value(Document{{"STR", 1}})};
    ASSERT_VALUE_EQ(notExpression->serialize(false), Value(Document{{"STR", arguments}}));
}