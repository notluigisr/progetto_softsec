TEST_F(DocumentSourceMatchTest, MultipleMatchStagesShouldCombineIntoOne) {
    auto match1 = DocumentSourceMatch::create(BSON("STR" << 1), getExpCtx());
    auto match2 = DocumentSourceMatch::create(BSON("STR" << 1), getExpCtx());
    auto match3 = DocumentSourceMatch::create(BSON("STR" << 1), getExpCtx());

    Pipeline::SourceContainer container;

    
    ASSERT_BSONOBJ_EQ(match1->getQuery(), BSON("STR" << 1));
    ASSERT_BSONOBJ_EQ(match2->getQuery(), BSON("STR" << 1));
    ASSERT_BSONOBJ_EQ(match3->getQuery(), BSON("STR" << 1));

    container.push_back(match1);
    container.push_back(match2);
    match1->optimizeAt(container.begin(), &container);

    ASSERT_EQUALS(container.size(), 1U);
    ASSERT_BSONOBJ_EQ(match1->getQuery(), fromjson("STR"));

    container.push_back(match3);
    match1->optimizeAt(container.begin(), &container);
    ASSERT_EQUALS(container.size(), 1U);
    ASSERT_BSONOBJ_EQ(match1->getQuery(),
                      fromjson("STR"
                               "STR"));
}