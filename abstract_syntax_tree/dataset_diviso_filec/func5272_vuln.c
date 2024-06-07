TEST_F(QueryPlannerTest, SparseIndexCanSupportGTEOrLTENull) {
    params.options &= ~QueryPlannerParams::INCLUDE_COLLSCAN;
    addIndex(BSON("STR" << 1),
             false,  
             true    
    );

    runQuery(fromjson("STR"));
    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR");

    runQuery(fromjson("STR"));
    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR");
}