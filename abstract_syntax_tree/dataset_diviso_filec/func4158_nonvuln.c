TEST(UriSuite, TestUriUserInfoHostPort2) {
		
		UriParserStateA stateA;
		UriUriA uriA;
		stateA.uri = &uriA;
		
		const char * const input = "STR"
		
				"STR";
		ASSERT_TRUE(0 == uriParseUriA(&stateA, input));

		ASSERT_TRUE(uriA.userInfo.first == input + 4 + 3);
		ASSERT_TRUE(uriA.userInfo.afterLast == input + 4 + 3 + 7);
		ASSERT_TRUE(uriA.hostText.first == input + 4 + 3 + 7 + 1);
		ASSERT_TRUE(uriA.hostText.afterLast == input + 4 + 3 + 7 + 1 + 9);
		ASSERT_TRUE(uriA.portText.first == input + 4 + 3 + 7 + 1 + 9 + 1);
		ASSERT_TRUE(uriA.portText.afterLast == input + 4 + 3 + 7 + 1 + 9 + 1 + 3);
		uriFreeUriMembersA(&uriA);
}