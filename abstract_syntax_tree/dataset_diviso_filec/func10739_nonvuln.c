static void __init of_unittest_overlay_1(void)
{
	
	if (of_unittest_apply_overlay_check(1, 1, 1, 0, PDEV_OVERLAY))
		return;

	unittest(1, "STR", 1);
}