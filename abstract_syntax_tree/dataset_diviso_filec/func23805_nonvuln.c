GF_Err prft_box_dump(GF_Box *a, FILE * trace)
{
	Double fracs;
	GF_ProducerReferenceTimeBox *ptr = (GF_ProducerReferenceTimeBox *) a;
	time_t secs;
	struct tm t;
	secs = (ptr->ntp >> 32) - GF_NTP_SEC_1900_TO_1970;
	if (secs < 0) {
		if (ptr->size) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("STR"));
		}
		secs = 0;
	}
	t = *gf_gmtime(&secs);
	fracs = (Double) (ptr->ntp & 0xFFFFFFFFULL);
	fracs /= 0xFFFFFFFF;
	fracs *= 1000;
	gf_isom_box_dump_start(a, "STR", trace);

	gf_fprintf(trace, "STR", ptr->refTrackID, ptr->timestamp, ptr->ntp, 1900+t.tm_year, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, (u32) t.tm_sec, (u32) fracs);
	gf_isom_box_dump_done("STR", a, trace);

	return GF_OK;
}