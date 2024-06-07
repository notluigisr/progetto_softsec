GF_Err ghnt_box_dump(GF_Box *a, FILE * trace)
{
	char *name;
	GF_HintSampleEntryBox *p;
	p = (GF_HintSampleEntryBox *)a;

	if (a->type == GF_ISOM_BOX_TYPE_RTP_STSD) {
		name = "STR";
	} else if (a->type == GF_ISOM_BOX_TYPE_SRTP_STSD) {
		name = "STR";
	} else if (a->type == GF_ISOM_BOX_TYPE_FDP_STSD) {
		name = "STR";
	} else if (a->type == GF_ISOM_BOX_TYPE_RRTP_STSD) {
		name = "STR";
	} else if (a->type == GF_ISOM_BOX_TYPE_RTCP_STSD) {
		name = "STR";
	} else {
		name = "STR";
	}
	gf_isom_box_dump_start(a, name, trace);
	gf_fprintf(trace, "STR", p->dataReferenceIndex, p->HintTrackVersion, p->LastCompatibleVersion);
	if ((a->type == GF_ISOM_BOX_TYPE_RTP_STSD) || (a->type == GF_ISOM_BOX_TYPE_SRTP_STSD) || (a->type == GF_ISOM_BOX_TYPE_RRTP_STSD) || (a->type == GF_ISOM_BOX_TYPE_RTCP_STSD)) {
		gf_fprintf(trace, "STR", p->MaxPacketSize);
	} else if (a->type == GF_ISOM_BOX_TYPE_FDP_STSD) {
		gf_fprintf(trace, "STR", p->partition_entry_ID, p->FEC_overhead);
	}
	gf_fprintf(trace, "STR");

	gf_isom_box_dump_done(name, a, trace);
	return GF_OK;
}