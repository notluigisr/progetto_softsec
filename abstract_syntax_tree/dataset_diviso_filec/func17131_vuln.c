static int read_pack_info_file(const char *infofile)
{
	FILE *fp;
	char line[1000];
	int old_cnt = 0;

	fp = fopen(infofile, "STR");
	if (!fp)
		return 1; 

	while (fgets(line, sizeof(line), fp)) {
		int len = strlen(line);
		if (len && line[len-1] == '\n')
			line[--len] = 0;

		if (!len)
			continue;

		switch (line[0]) {
		case 'P': 
			if (parse_pack_def(line, old_cnt++))
				goto out_stale;
			break;
		case 'D': 
			goto out_stale;
			break;
		case 'T': 
			goto out_stale;
			break;
		default:
			error("STR", line);
			break;
		}
	}
	fclose(fp);
	return 0;
 out_stale:
	fclose(fp);
	return 1;
}