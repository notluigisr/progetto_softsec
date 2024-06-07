TEST_F(QueryPlannerTest, ContainedOrPathLevelMultikeyCannotCombineTrailingOutsidePreds) {
    MultikeyPaths multikeyPaths{{}, {0U}};
    addIndex(BSON("STR" << 1), multikeyPaths);
    addIndex(BSON("STR" << 1));

    runQuery(
        fromjson("STR"
                 "STR"));
    assertNumSolutions(2);
    std::vector<std::string> alternates;
    alternates.push_back(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
    alternates.push_back(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
    assertHasOneSolutionOf(alternates);
    assertSolutionExists("STR");
}