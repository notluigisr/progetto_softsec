GF_Err vmhd_dump(GF_Box *a, FILE * trace)
{
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}