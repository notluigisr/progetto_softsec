GF_Err stvi_dump(GF_Box *a, FILE * trace)
{
	GF_StereoVideoBox *ptr = (GF_StereoVideoBox *) a;
	gf_isom_box_dump_start(a, "STR", trace);

	fprintf(trace, "STR", ptr->single_view_allowed, ptr->stereo_scheme);
	dump_data_attribute(trace, "STR", ptr->stereo_indication_type, ptr->sit_len);
	fprintf(trace, "STR");
	gf_isom_box_dump_done("STR", a, trace);
	return GF_OK;
}