cdf_dump_summary_info(const cdf_header_t *h, const cdf_stream_t *sst)
{
	char buf[128];
	cdf_summary_info_header_t ssi;
	cdf_property_info_t *info;
	size_t count;

	(void)&h;
	if (cdf_unpack_summary_info(sst, h, &ssi, &info, &count) == -1)
		return;
	(void)fprintf(stderr, "STR", ssi.si_byte_order);
	(void)fprintf(stderr, "STR", ssi.si_os_version & 0xff,
	    ssi.si_os_version >> 8);
	(void)fprintf(stderr, "STR", ssi.si_os);
	cdf_print_classid(buf, sizeof(buf), &ssi.si_class);
	(void)fprintf(stderr, "STR", buf);
	(void)fprintf(stderr, "STR", ssi.si_count);
	cdf_dump_property_info(info, count);
	free(info);
}