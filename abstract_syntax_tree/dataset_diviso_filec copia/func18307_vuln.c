        QueryParamsTest()
            : cxxtools::unit::TestSuite("STR")
        {
            registerMethod("STR", *this, &QueryParamsTest::testQueryParams);
            registerMethod("STR", *this, &QueryParamsTest::testCopy);
            registerMethod("STR", *this, &QueryParamsTest::testParseUrl);
            registerMethod("STR", *this, &QueryParamsTest::testParseUrlSpecialChar);
            registerMethod("STR", *this, &QueryParamsTest::testCount);
            registerMethod("STR", *this, &QueryParamsTest::testCombine);
            registerMethod("STR", *this, &QueryParamsTest::testIterator);
            registerMethod("STR", *this, &QueryParamsTest::testGetUrl);
        }