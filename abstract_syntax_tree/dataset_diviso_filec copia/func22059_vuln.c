TEST_F(OptimizePipeline, MultipleMatchesPushedDownWithSort) {
    auto unpack = fromjson(
        "STR"
        "STR");
    auto pipeline = Pipeline::parse(makeVector(unpack,
                                               fromjson("STR"),
                                               fromjson("STR"),
                                               fromjson("STR")),
                                    getExpCtx());
    ASSERT_EQ(4u, pipeline->getSources().size());

    pipeline->optimizePipeline();

    
    
    auto stages = pipeline->writeExplainOps(ExplainOptions::Verbosity::kQueryPlanner);
    ASSERT_EQ(4u, stages.size());
    ASSERT_BSONOBJ_EQ(fromjson("STR"
                               "STR"),
                      stages[0].getDocument().toBson());
    ASSERT_BSONOBJ_EQ(unpack, stages[1].getDocument().toBson());
    ASSERT_BSONOBJ_EQ(fromjson("STR"), stages[2].getDocument().toBson());
    ASSERT_BSONOBJ_EQ(fromjson("STR"), stages[3].getDocument().toBson());
}