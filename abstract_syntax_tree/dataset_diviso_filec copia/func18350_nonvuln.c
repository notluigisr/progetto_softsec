GF_Err text_dump(GF_Box *a, FILE * trace)
{
	GF_TextSampleEntryBox *p = (GF_TextSampleEntryBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	fprintf(trace, "STR",
	        p->dataReferenceIndex, p->displayFlags, p->textJustification);
	if (p->textName)
		fprintf(trace, "STR", p->textName);
	tx3g_dump_rgb16(trace, "STR", p->background_color);
	tx3g_dump_rgb16(trace, "STR", p->foreground_color);
	fprintf(trace, "STR");

	fprintf(trace, "STR");
	tx3g_dump_box(trace, &p->default_box);
	gf_isom_box_dump_done("STR", a, trace);
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}