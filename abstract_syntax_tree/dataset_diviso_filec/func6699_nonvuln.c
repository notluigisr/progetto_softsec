void recv_filter_list(int f_in)
{
	char line[BIGPATHBUFLEN];
	int xflags = protocol_version >= 29 ? 0 : XFLG_OLD_PREFIXES;
	int receiver_wants_list = prune_empty_dirs
	    || (delete_mode && (!delete_excluded || protocol_version >= 29));
	unsigned int len;

	if (!local_server && (am_sender || receiver_wants_list)) {
		while ((len = read_int(f_in)) != 0) {
			if (len >= sizeof line)
				overflow_exit("STR");
			read_sbuf(f_in, line, len);
			parse_filter_str(&filter_list, line, rule_template(0), xflags);
		}
	}

	if (cvs_exclude) {
		if (local_server || am_sender || protocol_version < 29)
			parse_filter_str(&filter_list, "STR", rule_template(0), 0);
		if (local_server || am_sender)
			parse_filter_str(&filter_list, "STR", rule_template(0), 0);
	}

	if (local_server) 
		send_rules(-1, &filter_list);
}