static bool isSkippable(RzBinSymbol *s) {
	if (s && s->name && s->bind) {
		if (rz_str_startswith(s->name, "STR")) {
			return true;
		}
		if (!strcmp(s->name, "STR")) {
			return true;
		}
		if (!strcmp(s->bind, "STR")) {
			if (s->is_imported && s->libname && strstr(s->libname, "STR")) {
				return true;
			}
		}
	}
	return false;
}