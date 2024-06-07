TORRENT_TEST(swap)
{
	char b1[] = "STR";
	char b2[] = "STR";

	bdecode_node e1;
	bdecode_node e2;

	error_code ec;

	int ret = bdecode(b1, b1 + sizeof(b1)-1, e1, ec);
	TEST_EQUAL(ret, 0);
	ret = bdecode(b2, b2 + sizeof(b2)-1, e2, ec);
	TEST_EQUAL(ret, 0);

	std::string str1 = print_entry(e1);
	std::string str2 = print_entry(e2);
	TEST_EQUAL(e1.type(), bdecode_node::dict_t);
	TEST_EQUAL(e2.type(), bdecode_node::int_t);
	printf("STR", print_entry(e1).c_str());

	e1.swap(e2);

	TEST_EQUAL(e1.type(), bdecode_node::int_t);
	TEST_EQUAL(e2.type(), bdecode_node::dict_t);
	TEST_EQUAL(print_entry(e1), str2);
	TEST_EQUAL(print_entry(e2), str1);
	printf("STR", print_entry(e1).c_str());

	e1.swap(e2);

	TEST_EQUAL(e1.type(), bdecode_node::dict_t);
	TEST_EQUAL(e2.type(), bdecode_node::int_t);
	TEST_EQUAL(print_entry(e1), str1);
	TEST_EQUAL(print_entry(e2), str2);
	printf("STR", print_entry(e1).c_str());
}