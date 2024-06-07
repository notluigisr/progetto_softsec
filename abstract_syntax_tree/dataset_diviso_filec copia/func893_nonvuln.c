GF_Err trep_dump(GF_Box *a, FILE * trace)
{
	GF_TrackExtensionPropertiesBox *p = (GF_TrackExtensionPropertiesBox*)a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR", p->trackID);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}