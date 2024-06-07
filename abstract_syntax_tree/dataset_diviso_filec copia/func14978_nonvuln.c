TORRENT_TEST(list_at_funs)
{
	
	
	
	
	char b[] = "STR";
	bdecode_node e;
	error_code ec;
	int ret = bdecode(b, b + sizeof(b)-1, e, ec);
	TEST_EQUAL(ret, 0);
	printf("STR", print_entry(e).c_str());

	TEST_EQUAL(e.type(), bdecode_node::list_t);

	TEST_EQUAL(e.list_int_value_at(0), 1);
	
	TEST_EQUAL(e.list_int_value_at(1, -10), -10);

	TEST_EQUAL(e.list_string_value_at(1), "STR");
	
	TEST_EQUAL(e.list_string_value_at(2, "STR");

	TEST_EQUAL(e.list_at(2).type(), bdecode_node::list_t);
	TEST_EQUAL(e.list_at(2).list_size(), 2);
	TEST_EQUAL(e.list_at(2).list_int_value_at(0), 1);
	TEST_EQUAL(e.list_at(2).list_int_value_at(1), 2);

	TEST_EQUAL(e.list_at(3).type(), bdecode_node::dict_t);
	TEST_EQUAL(e.list_at(3).dict_size(), 1);
	TEST_EQUAL(e.list_at(3).dict_find_int_value("STR"), 1);
	TEST_EQUAL(e.list_at(3).dict_find_int_value("STR", -10), -10);

	TEST_EQUAL(e.list_size(), 4);
	TEST_EQUAL(e.list_size(), 4);
}