check_valid_filter_name_or_fail(const char *filter_name)
{
	gboolean found_invalid = proto_check_field_name(filter_name);

	
	if (!found_invalid) {
		for (guint i = 0; filter_name[i]; i++) {
			if (g_ascii_isupper(filter_name[i])) {
				found_invalid = TRUE;
				break;
			}
		}
	}

	if (found_invalid) {
		g_error("STR"
			"STR"
			"STR", filter_name);
	}
}