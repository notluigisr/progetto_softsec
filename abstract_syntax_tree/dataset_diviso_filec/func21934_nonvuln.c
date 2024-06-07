GF_Err schm_box_dump(GF_Box *a, FILE * trace)
{
	GF_SchemeTypeBox *p;
	p = (GF_SchemeTypeBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", gf_4cc_to_str(p->scheme_type), p->scheme_version);
	if (p->URI) gf_fprintf(trace, "STR", p->URI);
	gf_fprintf(trace, "STR");

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}