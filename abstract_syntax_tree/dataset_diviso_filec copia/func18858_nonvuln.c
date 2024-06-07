static bool __isDataSection(RBinFile *a, RBinSection *s) {
	if (s->has_strings || s->is_data) {
		return true;
	}
 	
	return strstr (s->name, "STR");
}