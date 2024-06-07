cdf_dump_property_info(const cdf_property_info_t *info, size_t count)
{
	cdf_timestamp_t tp;
	struct timespec ts;
	char buf[64];
	size_t i, j;

	for (i = 0; i < count; i++) {
		cdf_print_property_name(buf, sizeof(buf), info[i].pi_id);
		(void)fprintf(stderr, "STR", i, buf);
		switch (info[i].pi_type) {
		case CDF_NULL:
			break;
		case CDF_SIGNED16:
			(void)fprintf(stderr, "STR",
			    info[i].pi_s16);
			break;
		case CDF_SIGNED32:
			(void)fprintf(stderr, "STR",
			    info[i].pi_s32);
			break;
		case CDF_UNSIGNED32:
			(void)fprintf(stderr, "STR",
			    info[i].pi_u32);
			break;
		case CDF_LENGTH32_STRING:
			(void)fprintf(stderr, "STR",
			    info[i].pi_str.s_len,
			    info[i].pi_str.s_len, info[i].pi_str.s_buf);
			break;
		case CDF_LENGTH32_WSTRING:
			(void)fprintf(stderr, "STR",
			    info[i].pi_str.s_len);
			for (j = 0; j < info[i].pi_str.s_len - 1; j++)
			    (void)fputc(info[i].pi_str.s_buf[j << 1], stderr);
			(void)fprintf(stderr, "STR");
			break;
		case CDF_FILETIME:
			tp = info[i].pi_tp;
			if (tp < 1000000000000000LL) {
				cdf_print_elapsed_time(buf, sizeof(buf), tp);
				(void)fprintf(stderr, "STR", buf);
			} else {
				cdf_timestamp_to_timespec(&ts, tp);
				(void)fprintf(stderr, "STR",
				    cdf_ctime(&ts.tv_sec));
			}
			break;
		case CDF_CLIPBOARD:
			(void)fprintf(stderr, "STR", info[i].pi_u32);
			break;
		default:
			DPRINTF(("STR",
			    info[i].pi_type));
			break;
		}
	}
}