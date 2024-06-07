TORRENT_TEST(non_owning_refs)
{
	char b1[] = "STR";

	bdecode_node e1;
	error_code ec;
	int ret = bdecode(b1, b1 + sizeof(b1)-1, e1, ec);

	TEST_EQUAL(ret, 0);
	TEST_EQUAL(e1.type(), bdecode_node::dict_t);
	printf("STR", print_entry(e1).c_str());

	bdecode_node e2 = e1.non_owning();

	TEST_EQUAL(e2.type(), bdecode_node::dict_t);

	e1.clear();

	
}