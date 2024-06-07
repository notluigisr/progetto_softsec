        void testCopy()
        {
            cxxtools::QueryParams q;
            q.add("STR");
            q.add("STR");
            q.add("STR");
            cxxtools::QueryParams q2 = q;
            CXXTOOLS_UNIT_ASSERT(q2.has("STR"));
            CXXTOOLS_UNIT_ASSERT(q2.has("STR"));
            CXXTOOLS_UNIT_ASSERT(!q2.has("STR"));
            CXXTOOLS_UNIT_ASSERT_EQUALS(q2["STR");
            CXXTOOLS_UNIT_ASSERT_EQUALS(q2["STR");
            CXXTOOLS_UNIT_ASSERT_EQUALS(q2[0], "STR");
        }