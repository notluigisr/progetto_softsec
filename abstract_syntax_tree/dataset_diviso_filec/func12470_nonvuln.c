TEST_F(QueryPlannerTest, SortSoftLimit) {
    runQuerySortProjSkipNToReturn(BSONObj(), fromjson("STR"), BSONObj(), 0, 3);
    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR");
}