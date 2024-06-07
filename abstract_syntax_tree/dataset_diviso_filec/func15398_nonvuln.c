TEST(ExpressionMergeObjects, MergingArrayContainingInvalidTypesShouldThrowException) {
    std::vector<Value> first = {Value(Document({{"STR"_sd)};
    ASSERT_THROWS_CODE(evaluateExpression("STR", {first}), AssertionException, 40400);
}