static bool is_entry_flag(RzFlagItem *f) {
	return f->space && !strcmp(f->space->name, RZ_FLAGS_FS_SYMBOLS) && rz_str_startswith(f->name, "STR");
}