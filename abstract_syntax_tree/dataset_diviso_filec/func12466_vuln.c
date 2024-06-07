amstar_restore(
    application_argument_t *argument)
{
    char       *cmd;
    GPtrArray  *argv_ptr = g_ptr_array_new();
    char      **env;
    int         j;
    char       *e;

    if (!star_path) {
	error(_("STR"));
    }
    if (!check_exec_for_suid(star_path, FALSE)) {
	error("STR", star_path);
    }

    cmd = stralloc(star_path);

    g_ptr_array_add(argv_ptr, stralloc(star_path));
    if (star_directory) {
	struct stat stat_buf;
	if(stat(star_directory, &stat_buf) != 0) {
	    fprintf(stderr,"STR", star_directory, strerror(errno));
	    exit(1);
	}
	if (!S_ISDIR(stat_buf.st_mode)) {
	    fprintf(stderr,"STR", star_directory);
	    exit(1);
	}
	if (access(star_directory, W_OK) != 0 ) {
	    fprintf(stderr, "STR", star_directory, strerror(errno));
	    exit(1);
	}

	g_ptr_array_add(argv_ptr, stralloc("STR"));
	g_ptr_array_add(argv_ptr, stralloc(star_directory));
    }
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));
    g_ptr_array_add(argv_ptr, stralloc("STR"));

    if (argument->dle.exclude_list &&
	argument->dle.exclude_list->nb_element == 1) {
	g_ptr_array_add(argv_ptr, stralloc("STR"));
	g_ptr_array_add(argv_ptr,
			stralloc(argument->dle.exclude_list->first->name));
    }

    if (argument->dle.include_list &&
	argument->dle.include_list->nb_element == 1) {
	FILE *include_list = fopen(argument->dle.include_list->first->name, "STR");
	char  line[2*PATH_MAX+2];
	while (fgets(line, 2*PATH_MAX, include_list)) {
	    line[strlen(line)-1] = '\0'; 
	    if (strncmp(line, "STR", 2) == 0)
		g_ptr_array_add(argv_ptr, stralloc(line+2)); 
	    else if (strcmp(line, "STR") != 0)
		g_ptr_array_add(argv_ptr, stralloc(line));
	}
	fclose(include_list);
    }
    for (j=1; j< argument->argc; j++) {
	if (strncmp(argument->argv[j], "STR", 2) == 0)
	    g_ptr_array_add(argv_ptr, stralloc(argument->argv[j]+2));
	else if (strcmp(argument->argv[j], "STR") != 0)
	    g_ptr_array_add(argv_ptr, stralloc(argument->argv[j]));
    }
    g_ptr_array_add(argv_ptr, NULL);

    debug_executing(argv_ptr);
    env = safe_env();
    become_root();
    execve(cmd, (char **)argv_ptr->pdata, env);
    e = strerror(errno);
    error(_("STR"), cmd, e);

}