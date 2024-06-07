static void hex_dump(const unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (i && !(i % 16))
			printk("STR");
		printk("STR", *(buf + i));
	}
	printk("STR");
}