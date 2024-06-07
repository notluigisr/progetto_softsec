GF_Err ftab_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_FontTableBox *p = (GF_FontTableBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR");
	for (i=0; i<p->entry_count; i++) {
		fprintf(trace, "STR");
	}
	if (!p->size) {
		fprintf(trace, "STR");
	}
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}