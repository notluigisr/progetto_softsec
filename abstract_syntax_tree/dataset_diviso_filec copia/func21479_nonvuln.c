GF_Err moof_box_dump(GF_Box *a, FILE * trace)
{
	GF_MovieFragmentBox *p;
	p = (GF_MovieFragmentBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", gf_list_count(p->TrackList));
	if (p->internal_flags & GF_ISOM_BOX_COMPRESSED)
		gf_fprintf(trace, "STR", p->size - p->compressed_diff);
	gf_fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}