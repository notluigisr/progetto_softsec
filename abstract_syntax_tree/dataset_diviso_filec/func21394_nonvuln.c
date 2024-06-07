TEST_F(QueryPlannerTest, UniqueIndexLookup) {
    params.options = QueryPlannerParams::INDEX_INTERSECTION;
    params.options |= QueryPlannerParams::NO_TABLE_SCAN;

    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1),
             false,  
             false,  
             true);  

    runQuery(fromjson("STR"));

    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR");
}