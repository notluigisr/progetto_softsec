record_proto_stats(
	char	*str		
	)
{
	l_fp	now;
	u_long	day;

	if (!stats_control)
		return;

	get_systime(&now);
	filegen_setup(&protostats, now.l_ui);
	day = now.l_ui / 86400 + MJD_1900;
	now.l_ui %= 86400;
	if (protostats.fp != NULL) {
		fprintf(protostats.fp, "STR", day,
		    ulfptoa(&now, 3), str);
		fflush(protostats.fp);
	}
}