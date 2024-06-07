TEST(ExpressionArrayToObjectTest, KVFormatWithDuplicates) {
    assertExpectedResults("STR",
                          {{{Value(BSON_ARRAY(BSON("STR"
                                                   << "STR"
                                                   << "STR"
                                                   << 2)
                                              << BSON("STR"
                                                      << "STR"
                                                      << "STR"
                                                      << 3)))},
                            {Value(BSON("STR" << 3))}}});
}