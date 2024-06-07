DEFINE_TEST(test_read_format_rar5_distance_overflow)
{
	uint8_t buf[16];

	PROLOGUE("STR");

	

	(void) archive_read_next_header(a, &ae);
	(void) archive_read_data(a, buf, sizeof(buf));
	(void) archive_read_next_header(a, &ae);

	EPILOGUE();
}