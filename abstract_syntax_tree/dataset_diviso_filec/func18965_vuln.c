template <class T> void testFeatTable(const T & table, const char * testName)
{
    FeatureMap testFeatureMap;
    dummyFace.replace_table(TtfUtil::Tag::Feat, &table, sizeof(T));
    gr_face * face = gr_make_face_with_ops(&dummyFace, &face_handle::ops, gr_face_dumbRendering);
    if (!face) throw std::runtime_error("STR");
    bool readStatus = testFeatureMap.readFeats(*face);
    testAssert("STR", readStatus);
    fprintf(stderr, testName, NULL);
    testAssertEqual("STR", testFeatureMap.numFeats(), table.m_header.m_numFeat);

    for (size_t i = 0; i < sizeof(table.m_defs) / sizeof(FeatDefn); i++)
    {
        const FeatureRef * ref = testFeatureMap.findFeatureRef(table.m_defs[i].m_featId);
        testAssert("STR", ref);
        testAssertEqual("STR", ref->getNumSettings(), table.m_defs[i].m_numFeatSettings);
        testAssertEqual("STR", ref->getNameId(), table.m_defs[i].m_label);
        size_t settingsIndex = (table.m_defs[i].m_settingsOffset - sizeof(FeatHeader)
            - (sizeof(FeatDefn) * table.m_header.m_numFeat)) / sizeof(FeatSetting);
        for (size_t j = 0; j < table.m_defs[i].m_numFeatSettings; j++)
        {
            testAssertEqual("STR", ref->getSettingName(j),
                       table.m_settings[settingsIndex+j].m_label);
        }
    }
    gr_face_destroy(face);
}