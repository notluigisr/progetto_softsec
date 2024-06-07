TEST_F(QueryPlannerTest, EmptyQueryWithProjectionUsesCollscanIfIndexIsGeo) {
    params.options = QueryPlannerParams::GENERATE_COVERED_IXSCANS;
    addIndex(BSON("STR"
                  << "STR"));
    runQueryAsCommand(fromjson("STR"));
    assertNumSolutions(1);
    assertSolutionExists(
        "STR"
        "STR");
}