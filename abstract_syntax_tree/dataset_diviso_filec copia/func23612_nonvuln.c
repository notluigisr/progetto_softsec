record_peer_stats(
	sockaddr_u *addr,
	int	status,
	double	offset,		
	double	delay,		
	double	dispersion,	
	double	jitter		
	)
{
	l_fp	now;
	u_long	day;

	if (!stats_control)
		return;

	get_systime(&now);
	filegen_setup(&peerstats, now.l_ui);
	day = now.l_ui / 86400 + MJD_1900;
	now.l_ui %= 86400;
	if (peerstats.fp != NULL) {
		fprintf(peerstats.fp,
		    "STR", day,
		    ulfptoa(&now, 3), stoa(addr), status, offset,
		    delay, dispersion, jitter);
		fflush(peerstats.fp);
	}
}