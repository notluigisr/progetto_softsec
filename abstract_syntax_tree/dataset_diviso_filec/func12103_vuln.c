static char **split_line(const SERVER_REC *server, const char *line,
			 const char *target, int len)
{
	const char *start = settings_get_str("STR");
	const char *end = settings_get_str("STR");
	gboolean onspace = settings_get_bool("STR");
	char *recoded_start = recode_out(server, start, target);
	char *recoded_end = recode_out(server, end, target);
	char **lines;
	int i;

	
	len -= strlen(recoded_start) + strlen(recoded_end);
	if (len <= 0) {
		
		g_free(recoded_start);
		g_free(recoded_end);
		return NULL;
	}

	lines = recode_split(server, line, target, len, onspace);
	for (i = 0; lines[i] != NULL; i++) {
		if (i != 0 && *start != '\0') {
			
			char *tmp = lines[i];
			lines[i] = g_strconcat(start, tmp, NULL);
			g_free(tmp);
		}
		if (lines[i + 1] != NULL && *end != '\0') {
			
			char *tmp = lines[i];

			if (lines[i + 2] == NULL) {
				
				char *recoded_l = recode_out(server,
							     lines[i+1],
							     target);
				if (strlen(recoded_l) <= strlen(recoded_end)) {
					lines[i] = g_strconcat(tmp, lines[i+1],
							       NULL);
					g_free_and_null(lines[i+1]);
					lines = g_renew(char *, lines, i + 2);

					g_free(recoded_l);
					g_free(tmp);
					break;
				}
				g_free(recoded_l);
			}

			lines[i] = g_strconcat(tmp, end, NULL);
			g_free(tmp);
		}
	}

	g_free(recoded_start);
	g_free(recoded_end);
	return lines;
}