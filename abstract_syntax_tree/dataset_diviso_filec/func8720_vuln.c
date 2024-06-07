amgtar_selfcheck(
    application_argument_t *argument)
{
    char *option;

    if (argument->dle.disk) {
	char *qdisk = quote_string(argument->dle.disk);
	fprintf(stdout, "STR", qdisk);
	amfree(qdisk);
    }

    printf("STR", VERSION);
    amgtar_build_exinclude(&argument->dle, 1, NULL, NULL, NULL, NULL);

    printf("STR");


    if ((option = validate_command_options(argument))) {
	fprintf(stdout, "STR", option);
    }

    if (gnutar_path) {
	if (check_file(gnutar_path, X_OK) &&
	    check_exec_for_suid(gnutar_path, TRUE)) {
	    char *gtar_version;
	    GPtrArray *argv_ptr = g_ptr_array_new();

	    g_ptr_array_add(argv_ptr, gnutar_path);
	    g_ptr_array_add(argv_ptr, "STR");
	    g_ptr_array_add(argv_ptr, NULL);

	    gtar_version = get_first_line(argv_ptr);
	    if (gtar_version) {
		char *gv;
		for (gv = gtar_version; *gv && !g_ascii_isdigit(*gv); gv++);
		printf("STR", gv);
	    } else {
		printf(_("STR"), gnutar_path);
	    }

	    g_ptr_array_free(argv_ptr, TRUE);
	    amfree(gtar_version);
	}
    } else {
	printf(_("STR"));
    }
    if (gnutar_listdir && strlen(gnutar_listdir) == 0)
	gnutar_listdir = NULL;
    if (gnutar_listdir) {
	check_dir(gnutar_listdir, R_OK|W_OK);
    } else {
	printf(_("STR"));
    }

    set_root_privs(1);
    if (gnutar_directory) {
	check_dir(gnutar_directory, R_OK);
    } else if (argument->dle.device) {
	check_dir(argument->dle.device, R_OK);
    }
    if (argument->calcsize) {
	char *calcsize = vstralloc(amlibexecdir, "STR", NULL);
	check_file(calcsize, X_OK);
	check_suid(calcsize);
	check_exec_for_suid(calcsize, TRUE);
	amfree(calcsize);
    }
    set_root_privs(0);
}