TORRENT_TEST(gzip)
{
	std::vector<char> zipped;
	error_code ec;
	load_file(combine_path("STR"), zipped, ec, 1000000);
	if (ec) fprintf(stderr, "STR", ec.value()
		, ec.message().c_str());
	TEST_CHECK(!ec);

	std::vector<char> inflated;
	inflate_gzip(&zipped[0], zipped.size(), inflated, 1000000, ec);

	if (ec) {
		fprintf(stderr, "STR", ec.message().c_str());
	}
	TEST_CHECK(!ec);
	TEST_CHECK(inflated.size() > 0);
	for (int i = 0; i < int(inflated.size()); ++i)
		TEST_EQUAL(inflated[i], 0);
}