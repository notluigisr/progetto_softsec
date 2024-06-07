TEST_F(QueryPlannerTest, ShardFilterBasicIndex) {
    params.options = QueryPlannerParams::INCLUDE_SHARD_FILTER;
    params.shardKey = BSON("STR" << 1);
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));

    runQuery(fromjson("STR"));

    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
}