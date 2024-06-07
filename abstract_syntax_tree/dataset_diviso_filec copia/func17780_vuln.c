vrrp_print_stats(void)
{
	FILE *file;
	file = fopen (stats_file, "STR");

	if (!file) {
		log_message(LOG_INFO, "STR",
			stats_file, errno, strerror(errno));
		return;
	}

	list l = vrrp_data->vrrp;
	element e;
	vrrp_t *vrrp;

	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vrrp = ELEMENT_DATA(e);
		fprintf(file, "STR", vrrp->iname);
		fprintf(file, "STR");
		fprintf(file, "STR", vrrp->stats->advert_rcvd);
		fprintf(file, "STR", vrrp->stats->advert_sent);
		fprintf(file, "STR", vrrp->stats->become_master);
		fprintf(file, "STR",
			vrrp->stats->release_master);
		fprintf(file, "STR");
		fprintf(file, "STR", vrrp->stats->packet_len_err);
		fprintf(file, "STR", vrrp->stats->ip_ttl_err);
		fprintf(file, "STR",
			vrrp->stats->invalid_type_rcvd);
		fprintf(file, "STR",
			vrrp->stats->advert_interval_err);
		fprintf(file, "STR",
			vrrp->stats->addr_list_err);
		fprintf(file, "STR");
		fprintf(file, "STR",
			vrrp->stats->invalid_authtype);
#ifdef _WITH_VRRP_AUTH_
		fprintf(file, "STR",
			vrrp->stats->authtype_mismatch);
		fprintf(file, "STR",
			vrrp->stats->auth_failure);
#endif
		fprintf(file, "STR");
		fprintf(file, "STR", vrrp->stats->pri_zero_rcvd);
		fprintf(file, "STR", vrrp->stats->pri_zero_sent);
	}
	fclose(file);
}