GF_Err mvhd_box_dump(GF_Box *a, FILE * trace)
{
	GF_MovieHeaderBox *p;

	p = (GF_MovieHeaderBox *) a;

	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->creationTime);
	gf_fprintf(trace, "STR", p->modificationTime);
	gf_fprintf(trace, "STR", p->timeScale);
	gf_fprintf(trace, "STR", p->duration);
	gf_fprintf(trace, "STR", p->nextTrackID);

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}