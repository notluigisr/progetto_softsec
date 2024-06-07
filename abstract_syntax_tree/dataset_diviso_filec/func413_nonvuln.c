TORRENT_TEST(dict_find_funs2)
{
	
	
	
	
	char b[] = "STR";
	bdecode_node e;
	error_code ec;
	int ret = bdecode(b, b + sizeof(b)-1, e, ec);
	TEST_EQUAL(ret, 0);
	printf("STR", print_entry(e).c_str());

	TEST_EQUAL(e.type(), bdecode_node::dict_t);

	
	TEST_EQUAL(e.dict_find("STR").type(), bdecode_node::dict_t);
	TEST_EQUAL(e.dict_find(std::string("STR")).type(), bdecode_node::dict_t);
}