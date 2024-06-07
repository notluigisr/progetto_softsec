GF_Err hdlr_dump(GF_Box *a, FILE * trace)
{
	GF_HandlerBox *p = (GF_HandlerBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	if (p->nameUTF8 && (u32) p->nameUTF8[0] == strlen(p->nameUTF8+1)) {
		fprintf(trace, "STR", gf_4cc_to_str(p->handlerType), p->nameUTF8+1);
	} else {
		fprintf(trace, "STR", gf_4cc_to_str(p->handlerType), p->nameUTF8);
	}
	fprintf(trace, "STR", p->reserved1);
	dump_data(trace, (char *) p->reserved2, 12);
	fprintf(trace, "STR");

	fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}