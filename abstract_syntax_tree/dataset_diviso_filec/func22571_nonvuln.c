GF_Err afra_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_AdobeFragRandomAccessBox *p = (GF_AdobeFragRandomAccessBox*)a;
	gf_isom_box_dump_start(a, "STR", trace);

	fprintf(trace, "STR", p->long_ids, p->long_offsets, p->time_scale);

	for (i=0; i<p->entry_count; i++) {
		GF_AfraEntry *ae = (GF_AfraEntry *)gf_list_get(p->local_access_entries, i);
		fprintf(trace, "STR", ae->time, ae->offset);
	}

	for (i=0; i<p->global_entry_count; i++) {
		GF_GlobalAfraEntry *gae = (GF_GlobalAfraEntry *)gf_list_get(p->global_access_entries, i);
		fprintf(trace, "STR",
		        gae->time, gae->segment, gae->fragment, gae->afra_offset, gae->offset_from_afra);
	}

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}