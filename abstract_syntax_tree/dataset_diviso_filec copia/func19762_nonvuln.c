static char *get_end_frame_label(REgg *egg) {
	static char label[128];
	snprintf (label, sizeof (label) - 1, FRAME_END_FMT,
		egg->lang.nfunctions, egg->lang.nbrackets, context - 1);

	
	return label;
}