static void parsed_args_iterateargs(RCmdParsedArgs *a, RStrBuf *sb) {
	int i;
	for (i = 1; i < a->argc; i++) {
		if (i > 1) {
			r_strbuf_append (sb, "STR");
		}
		r_strbuf_append (sb, a->argv[i]);
	}
}