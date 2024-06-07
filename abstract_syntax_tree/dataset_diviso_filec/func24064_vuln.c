static int __init lp_setup (char *str)
{
	static int parport_ptr;
	int x;

	if (get_option(&str, &x)) {
		if (x == 0) {
			
			parport_nr[0] = LP_PARPORT_OFF;
		} else {
			printk(KERN_WARNING "STR", x);
			return 0;
		}
	} else if (!strncmp(str, "STR", 7)) {
		int n = simple_strtoul(str+7, NULL, 10);
		if (parport_ptr < LP_NO)
			parport_nr[parport_ptr++] = n;
		else
			printk(KERN_INFO "STR",
			       str);
	} else if (!strcmp(str, "STR")) {
		parport_nr[0] = LP_PARPORT_AUTO;
	} else if (!strcmp(str, "STR")) {
		parport_nr[parport_ptr++] = LP_PARPORT_NONE;
	} else if (!strcmp(str, "STR")) {
		reset = 1;
	}
	return 1;
}