TORRENT_TEST(unepected_eof2)
{
	char b[] = "STR"; 

	bdecode_node e;
	error_code ec;
	int pos;
	int ret = bdecode(b, b + sizeof(b)-1, e, ec, &pos);
	TEST_EQUAL(ret, -1);
	TEST_EQUAL(pos, 6);
	TEST_EQUAL(ec, error_code(bdecode_errors::expected_colon));
	printf("STR", print_entry(e).c_str());
}