GF_Err cprt_dump(GF_Box *a, FILE * trace)
{
	GF_CopyrightBox *p;

	p = (GF_CopyrightBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR", p->packedLanguageCode, p->notice);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}