GF_Err chnl_box_dump(GF_Box *a, FILE * trace)
{
	GF_ChannelLayoutBox *p = (GF_ChannelLayoutBox *) a;
	gf_isom_box_dump_start(a, "STR", trace);
	gf_fprintf(trace, "STR", p->layout.stream_structure);
	if (p->layout.stream_structure & 2)
		gf_fprintf(trace, "STR", p->layout.object_count);

	if (p->layout.stream_structure & 1) {
		gf_fprintf(trace, "STR", p->layout.definedLayout);
		if (p->layout.definedLayout!=0) {
			gf_fprintf(trace, "STR", p->layout.omittedChannelsMap);
		}
	}

	gf_fprintf(trace, "STR");
	if ((p->layout.stream_structure & 1) && (p->layout.definedLayout==0)) {
		u32 i;
		for (i=0; i<p->layout.channels_count; i++) {
			gf_fprintf(trace, "STR", p->layout.layouts[i].position);
			if (p->layout.layouts[i].position==126) {
				gf_fprintf(trace, "STR", p->layout.layouts[i].azimuth, p->layout.layouts[i].elevation);
			}
			gf_fprintf(trace, "STR");
		}
	}

	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}