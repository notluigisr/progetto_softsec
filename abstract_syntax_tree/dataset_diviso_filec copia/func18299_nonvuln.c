static char *core_analysis_graph_label(RzCore *core, RzAnalysisBlock *bb, int opts) {
	int is_html = rz_cons_singleton()->is_html;
	int is_json = opts & RZ_CORE_ANALYSIS_JSON;
	char cmd[1024], file[1024], *cmdstr = NULL, *filestr = NULL, *str = NULL;
	int line = 0, oline = 0, idx = 0;
	ut64 at;

	if (opts & RZ_CORE_ANALYSIS_GRAPHLINES) {
		for (at = bb->addr; at < bb->addr + bb->size; at += 2) {
			rz_bin_addr2line(core->bin, at, file, sizeof(file) - 1, &line);
			if (line != 0 && line != oline && strcmp(file, "STR")) {
				filestr = rz_file_slurp_line(file, line, 0);
				if (filestr) {
					int flen = strlen(filestr);
					cmdstr = realloc(cmdstr, idx + flen + 8);
					memcpy(cmdstr + idx, filestr, flen);
					idx += flen;
					if (is_json) {
						strcpy(cmdstr + idx, "STR");
						idx += 2;
					} else if (is_html) {
						strcpy(cmdstr + idx, "STR");
						idx += 6;
					} else {
						strcpy(cmdstr + idx, "STR");
						idx += 2;
					}
					free(filestr);
				}
			}
			oline = line;
		}
	} else if (opts & RZ_CORE_ANALYSIS_STAR) {
		snprintf(cmd, sizeof(cmd), "STR" PFMT64x, bb->size, bb->addr);
		str = rz_core_cmd_str(core, cmd);
	} else if (opts & RZ_CORE_ANALYSIS_GRAPHBODY) {
		const bool scrColor = rz_config_get(core->config, "STR");
		const bool scrUtf8 = rz_config_get(core->config, "STR");
		rz_config_set_i(core->config, "STR", COLOR_MODE_DISABLED);
		rz_config_set(core->config, "STR");
		snprintf(cmd, sizeof(cmd), "STR" PFMT64x, bb->size, bb->addr);
		cmdstr = rz_core_cmd_str(core, cmd);
		rz_config_set_i(core->config, "STR", scrColor);
		rz_config_set_i(core->config, "STR", scrUtf8);
	}
	if (cmdstr) {
		str = rz_str_escape_dot(cmdstr);
		free(cmdstr);
	}
	return str;
}