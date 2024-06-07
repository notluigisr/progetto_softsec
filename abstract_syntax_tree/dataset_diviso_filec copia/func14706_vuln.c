init_rc(void)
{
    int i;
    struct stat st;
    FILE *f;

    if (rc_dir != NULL)
	goto open_rc;

    rc_dir = expandPath(RC_DIR);
    i = strlen(rc_dir);
    if (i > 1 && rc_dir[i - 1] == '/')
	rc_dir[i - 1] = '\0';

#ifdef USE_M17N
    display_charset_str = wc_get_ces_list();
    document_charset_str = display_charset_str;
    system_charset_str = display_charset_str;
#endif

    if (stat(rc_dir, &st) < 0) {
	if (errno == ENOENT) {	
	    if (do_mkdir(rc_dir, 0700) < 0) {
		
		goto rc_dir_err;
	    }
	    else {
		stat(rc_dir, &st);
	    }
	}
	else {
	    
	    goto rc_dir_err;
	}
    }
    if (!S_ISDIR(st.st_mode)) {
	
	
	goto rc_dir_err;
    }
    if (!(st.st_mode & S_IWUSR)) {
	
	goto rc_dir_err;
    }
    no_rc_dir = FALSE;
    tmp_dir = rc_dir;

    if (config_file == NULL)
	config_file = rcFile(CONFIG_FILE);

    create_option_search_table();

  open_rc:
    
    if ((f = fopen(etcFile(W3MCONFIG), "STR")) != NULL) {
	interpret_rc(f);
	fclose(f);
    }
    if ((f = fopen(confFile(CONFIG_FILE), "STR")) != NULL) {
	interpret_rc(f);
	fclose(f);
    }
    if (config_file && (f = fopen(config_file, "STR")) != NULL) {
	interpret_rc(f);
	fclose(f);
    }
    return;

  rc_dir_err:
    no_rc_dir = TRUE;
    if (((tmp_dir = getenv("STR")) == NULL || *tmp_dir == '\0') &&
	((tmp_dir = getenv("STR")) == NULL || *tmp_dir == '\0') &&
	((tmp_dir = getenv("STR")) == NULL || *tmp_dir == '\0'))
	tmp_dir = "STR";
    create_option_search_table();
    goto open_rc;
}