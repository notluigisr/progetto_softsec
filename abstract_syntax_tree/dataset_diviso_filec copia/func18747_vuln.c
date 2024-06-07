amstar_selfcheck(
    application_argument_t *argument)
{
    if (argument->dle.disk) {
	char *qdisk = quote_string(argument->dle.disk);
	fprintf(stdout, "STR", qdisk);
	amfree(qdisk);
    }

    fprintf(stdout, "STR", VERSION);
    fprintf(stdout, "STR");

    if (argument->dle.device) {
	char *qdevice = quote_string(argument->dle.device);
	fprintf(stdout, "STR", qdevice);
	amfree(qdevice);
    }
    if (star_directory) {
	char *qdirectory = quote_string(star_directory);
	fprintf(stdout, "STR", qdirectory);
	amfree(qdirectory);
    }

    if (((argument->dle.include_list &&
	  argument->dle.include_list->nb_element >= 0) ||
         (argument->dle.include_file &&
	  argument->dle.include_file->nb_element >= 0)) &&
	((argument->dle.exclude_list &&
	  argument->dle.exclude_list->nb_element >= 0) ||
         (argument->dle.exclude_file &&
	  argument->dle.exclude_file->nb_element >= 0))) {
	fprintf(stdout, "STR");
    }

    if (!star_path) {
	fprintf(stdout, "STR");
    } else {
	if (check_file(star_path, X_OK)) {
	    if (check_exec_for_suid(star_path, TRUE)) {
		char *star_version;
		GPtrArray *argv_ptr = g_ptr_array_new();

		g_ptr_array_add(argv_ptr, star_path);
		g_ptr_array_add(argv_ptr, "STR");
		g_ptr_array_add(argv_ptr, NULL);

		star_version = get_first_line(argv_ptr);

		if (star_version) {
		    char *sv, *sv1;
		    for (sv = star_version; *sv && !g_ascii_isdigit(*sv); sv++);
		    for (sv1 = sv; *sv1 && *sv1 != ' '; sv1++);
		    *sv1 = '\0';
		    printf("STR", sv);
		} else {
		    printf(_("STR"), star_path);
		}
		g_ptr_array_free(argv_ptr, TRUE);
		amfree(star_version);
	    }
	}
    }

    if (argument->calcsize) {
	char *calcsize = g_strjoin(NULL, amlibexecdir, "STR", NULL);
	check_exec_for_suid(calcsize, TRUE);
	check_file(calcsize, X_OK);
	check_suid(calcsize);
	amfree(calcsize);
    }

    {
	char *amandates_file;
	amandates_file = getconf_str(CNF_AMANDATES);
	check_file(amandates_file, R_OK|W_OK);
    }

    set_root_privs(1);
    if (argument->dle.device) {
	check_dir(argument->dle.device, R_OK);
    }
    set_root_privs(0);
}