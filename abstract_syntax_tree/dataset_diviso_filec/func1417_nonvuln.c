GF_Err trgr_dump(GF_Box *a, FILE * trace)
{
	GF_TrackGroupBox *ptr = (GF_TrackGroupBox *) a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR");
	gf_isom_box_array_dump(ptr->groups, trace);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}