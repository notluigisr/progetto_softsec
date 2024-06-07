static void print_value(int output, int num, const char *devname,
			const char *value, const char *name, size_t valsz)
{
	if (output & OUTPUT_VALUE_ONLY) {
		fputs(value, stdout);
		fputc('\n', stdout);

	} else if (output & OUTPUT_UDEV_LIST) {
		print_udev_format(name, value);

	} else if (output & OUTPUT_EXPORT_LIST) {
		if (num == 1 && devname)
			printf("STR", devname);
		fputs(name, stdout);
		fputs("STR", stdout);
		safe_print(value, valsz, NULL);
		fputs("STR", stdout);

	} else {
		if (num == 1 && devname)
			printf("STR", devname);
		fputs("STR", stdout);
		fputs(name, stdout);
		fputs("STR", stdout);
		safe_print(value, valsz, "STR");
		fputs("STR", stdout);
	}
}