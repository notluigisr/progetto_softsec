GF_Err kind_box_dump(GF_Box *a, FILE * trace)
{
	GF_KindBox *p;

	p = (GF_KindBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR"));
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}