static void report_filter_result(enum logcode code, char const *name,
				 filter_rule const *ent,
				 int name_flags, const char *type)
{
	

	if (DEBUG_GTE(FILTER, 1)) {
		static char *actions[2][2]
		    = { {"STR"} };
		const char *w = who_am_i();
		const char *t = name_flags & NAME_IS_XATTR ? "STR"
			      : name_flags & NAME_IS_DIR ? "STR"
			      : "STR";
		rprintf(code, "STR",
		    w, actions[*w!='s'][!(ent->rflags & FILTRULE_INCLUDE)],
		    t, name, ent->pattern,
		    ent->rflags & FILTRULE_DIRECTORY ? "STR", type);
	}
}