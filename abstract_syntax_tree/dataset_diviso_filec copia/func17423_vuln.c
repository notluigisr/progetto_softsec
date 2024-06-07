vrrp_print_data(void)
{
	FILE *file = fopen (dump_file, "STR");

	if (!file) {
		log_message(LOG_INFO, "STR",
			dump_file, errno, strerror(errno));
		return;
	}

	dump_data_vrrp(file);

	fclose(file);
}