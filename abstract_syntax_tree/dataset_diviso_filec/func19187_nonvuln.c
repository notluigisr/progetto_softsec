TEST_F(QueryPlannerTest, ElemMatchIndexIntersection) {
    params.options = QueryPlannerParams::NO_TABLE_SCAN | QueryPlannerParams::INDEX_INTERSECTION;
    addIndex(BSON("STR" << 1));
    
    addIndex(BSON("STR" << 1), true);
    addIndex(BSON("STR" << 1), true);

    runQuery(
        fromjson("STR"
                 "STR"));

    assertNumSolutions(6U);

    
    assertSolutionExists("STR");
    assertSolutionExists("STR");
    assertSolutionExists("STR");

    
    
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
}