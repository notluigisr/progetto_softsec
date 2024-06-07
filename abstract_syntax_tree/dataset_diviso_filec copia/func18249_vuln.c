ambsdtar_selfcheck(
    application_argument_t *argument)
{
    if (argument->dle.disk) {
	char *qdisk = quote_string(argument->dle.disk);
	fprintf(stdout, "STR", qdisk);
	amfree(qdisk);
    }

    printf("STR", VERSION);
    ambsdtar_build_exinclude(&argument->dle, 1, NULL, NULL, NULL, NULL);

    printf("STR");
    if (bsdtar_path) {
	if (check_file(bsdtar_path, X_OK)) {
	    if (check_exec_for_suid(bsdtar_path, TRUE)) {
		char *bsdtar_version;
		GPtrArray *argv_ptr = g_ptr_array_new();

		g_ptr_array_add(argv_ptr, bsdtar_path);
		g_ptr_array_add(argv_ptr, "STR");
		g_ptr_array_add(argv_ptr, NULL);

		bsdtar_version = get_first_line(argv_ptr);
		if (bsdtar_version) {
		    char *tv, *bv;
		    for (tv = bsdtar_version; *tv && !g_ascii_isdigit(*tv); tv++);
		    for (bv = tv; *bv && *bv != ' '; bv++);
		    if (*bv) *bv = '\0';
		    printf("STR", tv);
		} else {
		    printf(_("STR"), bsdtar_path);
		}

		g_ptr_array_free(argv_ptr, TRUE);
		amfree(bsdtar_version);
	    }
	}
    } else {
	printf(_("STR"));
    }

    set_root_privs(1);
    if (state_dir && strlen(state_dir) == 0)
	state_dir = NULL;
    if (state_dir) {
	check_dir(state_dir, R_OK|W_OK);
    } else {
	printf(_("STR"));
    }

    if (bsdtar_directory) {
	check_dir(bsdtar_directory, R_OK);
    } else if (argument->dle.device) {
	check_dir(argument->dle.device, R_OK);
    }

    if (argument->calcsize) {
	char *calcsize = g_strjoin(NULL, amlibexecdir, "STR", NULL);
	check_exec_for_suid(calcsize, TRUE);
	check_file(calcsize, X_OK);
	check_suid(calcsize);
	amfree(calcsize);
    }
    set_root_privs(0);
}