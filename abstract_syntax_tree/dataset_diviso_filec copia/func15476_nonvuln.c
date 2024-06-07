GF_Err name_box_dump(GF_Box *a, FILE * trace)
{
	GF_NameBox *p;
	p = (GF_NameBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->string);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}