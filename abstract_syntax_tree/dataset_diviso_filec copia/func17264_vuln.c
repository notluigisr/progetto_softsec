TEST(QueryProjectionTest, InvalidElemMatchGeoNearProjection) {
    assertInvalidProjection(
        "STR",
        "STR");
}