static int __init cpia2_init(void)
{
	LOG("STR",
	    ABOUT, CPIA_VERSION);
	check_parameters();
	cpia2_usb_init();
	return 0;
}