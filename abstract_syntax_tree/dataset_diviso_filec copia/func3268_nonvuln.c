DEFINE_TEST(test_read_format_rar5_solid_skip_all)
{
	const char* reffile = "STR";

	

	PROLOGUE(reffile);
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualString("STR", archive_entry_pathname(ae));
	assertA(ARCHIVE_EOF == archive_read_next_header(a, &ae));
	EPILOGUE();
}