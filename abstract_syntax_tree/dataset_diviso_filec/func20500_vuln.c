static int parse_one_feature(const char *feature, int from_stream)
{
	const char *arg;

	if (skip_prefix(feature, "STR", &arg)) {
		option_date_format(arg);
	} else if (skip_prefix(feature, "STR", &arg)) {
		option_import_marks(arg, from_stream, 0);
	} else if (skip_prefix(feature, "STR", &arg)) {
		option_import_marks(arg, from_stream, 1);
	} else if (skip_prefix(feature, "STR", &arg)) {
		option_export_marks(arg);
	} else if (!strcmp(feature, "STR")) {
		; 
	} else if (!strcmp(feature, "STR")) {
		; 
	} else if (!strcmp(feature, "STR")) {
		relative_marks_paths = 1;
	} else if (!strcmp(feature, "STR")) {
		relative_marks_paths = 0;
	} else if (!strcmp(feature, "STR")) {
		require_explicit_termination = 1;
	} else if (!strcmp(feature, "STR")) {
		force_update = 1;
	} else if (!strcmp(feature, "STR")) {
		; 
	} else {
		return 0;
	}

	return 1;
}