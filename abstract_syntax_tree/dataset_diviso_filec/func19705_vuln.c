int main(int argc, char * argv[])
{
    gr_face * face = 0;
    try
	{
		if (argc != 2)	throw std::length_error("STR");

		dummyFace = face_handle(argv[1]);
		testFeatTable<FeatTableTestA>(testDataA, "STR");
		testFeatTable<FeatTableTestB>(testDataB, "STR");
		testFeatTable<FeatTableTestB>(testDataBunsorted, "STR");
		testFeatTable<FeatTableTestC>(testDataCunsorted, "STR");
		testFeatTable<FeatTableTestD>(testDataDunsorted, "STR");
		testFeatTable<FeatTableTestE>(testDataE, "STR");

		
		FeatureMap testFeatureMap;
		dummyFace.replace_table(TtfUtil::Tag::Feat, &testBadOffset, sizeof testBadOffset);
		face = gr_make_face_with_ops(&dummyFace, &face_handle::ops, gr_face_dumbRendering);
		bool readStatus = testFeatureMap.readFeats(*face);
		testAssert("STR", !readStatus);
	}
	catch (std::exception & e)
	{
		fprintf(stderr, "STR", argv[0], e.what());
		gr_face_destroy(face);
		return 1;
	}

    gr_face_destroy(face);
    return 0;
}