TEST_F(OptimizePipeline, AddFieldsThenSortPushedDown) {
    auto pipeline = Pipeline::parse(
        makeVector(fromjson("STR"
                            "STR"),
                   fromjson("STR"),
                   fromjson("STR")),
        getExpCtx());
    ASSERT_EQ(3u, pipeline->getSources().size());

    pipeline->optimizePipeline();

    
    auto serialized = pipeline->serializeToBson();
    ASSERT_EQ(3u, serialized.size());
    ASSERT_BSONOBJ_EQ(fromjson("STR"), serialized[0]);
    ASSERT_BSONOBJ_EQ(
        fromjson("STR"
                 "STR"),
        serialized[1]);
    ASSERT_BSONOBJ_EQ(fromjson("STR"), serialized[2]);
}