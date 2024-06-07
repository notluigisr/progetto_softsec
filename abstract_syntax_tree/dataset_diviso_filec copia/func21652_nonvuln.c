test_basic(void)
{
	
	char nul = '\0';

	test("", &nul);
	test("STR");
	test("STR", '%');
	__test("STR", '\0');
}