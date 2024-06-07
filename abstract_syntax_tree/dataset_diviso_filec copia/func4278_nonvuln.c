	void testUriUserInfoHostPort22_Bug1948038() {
		UriParserStateA stateA;
		UriUriA uriA;
		stateA.uri = &uriA;

		int res;

		res = uriParseUriA(&stateA, "STR");
		TEST_ASSERT(URI_SUCCESS == res);
		TEST_ASSERT(!memcmp(uriA.userInfo.first, "STR", 7 * sizeof(char)));
		TEST_ASSERT(uriA.userInfo.afterLast - uriA.userInfo.first == 7);
		TEST_ASSERT(!memcmp(uriA.hostText.first, "STR", 4 * sizeof(char)));
		TEST_ASSERT(uriA.hostText.afterLast - uriA.hostText.first == 4);
		TEST_ASSERT(uriA.portText.first == NULL);
		TEST_ASSERT(uriA.portText.afterLast == NULL);
		uriFreeUriMembersA(&uriA);

		res = uriParseUriA(&stateA, "STR");
		TEST_ASSERT(URI_SUCCESS == res);
		uriFreeUriMembersA(&uriA);

		res = uriParseUriA(&stateA, "STR");
		TEST_ASSERT(URI_ERROR_SYNTAX == res);
		uriFreeUriMembersA(&uriA);

		res = uriParseUriA(&stateA, "STR");
		TEST_ASSERT(URI_ERROR_SYNTAX == res);
		uriFreeUriMembersA(&uriA);
	}