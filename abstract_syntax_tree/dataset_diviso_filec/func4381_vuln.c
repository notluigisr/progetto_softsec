plain(void)
{
	test(PTR1_ZEROES PTR1_STR "STR", PTR1, PTR2);
	
	test("STR",
	     "STR", PTR_WIDTH+2, PTR1, PTR_WIDTH+2, PTR1);
	test("STR",
	     "STR", PTR_WIDTH+2, PTR2, PTR_WIDTH+2, PTR2);

	
	test("STR", PTR1);
	test("STR", PTR2);
}