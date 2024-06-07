const GF_FilterRegister *writegen_register(GF_FilterSession *session)
{

	
	if (!strcmp(GenDumpCaps[3].val.value.string, "STR")) {
		GenDumpCaps[3].val.value.string = (char *) gf_pixel_fmt_all_shortnames();
		GenDumpCaps[8].val.value.string = (char *) gf_audio_fmt_all_shortnames();
		GenDumpArgs[1].min_max_enum = gf_pixel_fmt_all_names();
		GenDumpArgs[2].min_max_enum = gf_audio_fmt_all_names();
	}

	return &GenDumpRegister;
}