GF_Err stts_box_dump(GF_Box *a, FILE * trace)
{
	GF_TimeToSampleBox *p;
	u32 i, nb_samples;

	if (dump_skip_samples)
		return GF_OK;

	p = (GF_TimeToSampleBox *)a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->nb_entries);

	nb_samples = 0;
	for (i=0; i<p->nb_entries; i++) {
		gf_fprintf(trace, "STR", p->entries[i].sampleDelta, p->entries[i].sampleCount);
		nb_samples += p->entries[i].sampleCount;
	}
	if (p->size)
		gf_fprintf(trace, "STR", nb_samples);
	else
		gf_fprintf(trace, "STR");

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}