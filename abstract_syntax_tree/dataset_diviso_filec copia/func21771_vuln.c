struct torture_suite *torture_raw_write(TALLOC_CTX *mem_ctx)
{
	struct torture_suite *suite = torture_suite_create(mem_ctx, "STR");

	torture_suite_add_1smb_test(suite, "STR", test_write);
	torture_suite_add_1smb_test(suite, "STR", test_writeunlock);
	torture_suite_add_1smb_test(suite, "STR", test_writeclose);
	torture_suite_add_1smb_test(suite, "STR", test_writex);

	return suite;
}