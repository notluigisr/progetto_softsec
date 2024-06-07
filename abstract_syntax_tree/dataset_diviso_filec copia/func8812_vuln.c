TEST_F(InternalUnpackBucketSplitMatchOnMetaAndRename, OptimizeSplitsMatchAndMapsControlPredicates) {
    auto unpack = fromjson(
        "STR"
        "STR");
    auto pipeline = Pipeline::parse(
        makeVector(unpack, fromjson("STR")),
        getExpCtx());
    ASSERT_EQ(2u, pipeline->getSources().size());

    pipeline->optimizePipeline();

    
    
    
    auto serialized = pipeline->serializeToBson();
    ASSERT_EQ(3u, serialized.size());
    ASSERT_BSONOBJ_EQ(fromjson("STR"
                               "STR"),
                      serialized[0]);
    ASSERT_BSONOBJ_EQ(unpack, serialized[1]);
    ASSERT_BSONOBJ_EQ(fromjson("STR"), serialized[2]);
}