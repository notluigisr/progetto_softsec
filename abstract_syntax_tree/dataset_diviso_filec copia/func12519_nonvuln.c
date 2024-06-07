GF_Err chan_box_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_ChannelLayoutInfoBox *p = (GF_ChannelLayoutInfoBox *) a;

	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->layout_tag, p->bitmap);
	for (i=0; i<p->num_audio_description; i++) {
		GF_AudioChannelDescription *adesc = &p->audio_descs[i];
		gf_fprintf(trace, "STR", adesc->label, adesc->flags, adesc->coordinates[0], adesc->coordinates[1], adesc->coordinates[2]);
	}
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}