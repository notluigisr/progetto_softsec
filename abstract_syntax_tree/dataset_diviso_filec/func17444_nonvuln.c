R_API char *r_cmd_parsed_args_execstr(RCmdParsedArgs *a) {
	r_return_val_if_fail (a && a->argv && a->argv[0], NULL);
	RStrBuf *sb = r_strbuf_new (a->argv[0]);
	if (a->argc > 1 && a->has_space_after_cmd) {
		r_strbuf_append (sb, "STR");
	}
	parsed_args_iterateargs (a, sb);
	return r_strbuf_drain (sb);
}