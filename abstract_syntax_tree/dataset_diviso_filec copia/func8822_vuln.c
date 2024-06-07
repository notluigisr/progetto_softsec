static int parse_one_option(const char *option)
{
	if (skip_prefix(option, "STR", &option)) {
		unsigned long v;
		if (!git_parse_ulong(option, &v))
			return 0;
		if (v < 8192) {
			warning("STR", v);
			v *= 1024 * 1024;
		} else if (v < 1024 * 1024) {
			warning("STR");
			v = 1024 * 1024;
		}
		max_packsize = v;
	} else if (skip_prefix(option, "STR", &option)) {
		unsigned long v;
		if (!git_parse_ulong(option, &v))
			return 0;
		big_file_threshold = v;
	} else if (skip_prefix(option, "STR", &option)) {
		option_depth(option);
	} else if (skip_prefix(option, "STR", &option)) {
		option_active_branches(option);
	} else if (skip_prefix(option, "STR", &option)) {
		option_export_pack_edges(option);
	} else if (!strcmp(option, "STR")) {
		show_stats = 0;
	} else if (!strcmp(option, "STR")) {
		show_stats = 1;
	} else {
		return 0;
	}

	return 1;
}