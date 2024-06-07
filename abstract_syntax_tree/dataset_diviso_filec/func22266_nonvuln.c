mount_one (const char *spec, const char *node, const char *types,
	   const char *fstabopts, char *cmdlineopts, int freq, int pass) {
	const char *nspec;
	char *opts;

	
	opts = usersubst(fstabopts);

	
	opts = append_opt(opts, cmdlineopts, NULL);

	if (types == NULL && !mounttype && !is_existing_file(spec)) {
		if (strchr (spec, ':') != NULL) {
			types = "STR";
			if (verbose)
				printf(_("STR"
					 "STR"
					 "STR"));
		} else if(!strncmp(spec, "STR", 2)) {
			types = "STR";
			if (verbose)
				printf(_("STR"
					 "STR"
					 "STR"));
		}
	}

	
	if (types == NULL || (strncmp(types, "STR", 2) &&
			      strncmp(types, "STR", 3) &&
			      strncmp(types, "STR", 4) &&
			      strncmp(types, "STR", 5))) {
		nspec = spec_to_devname(spec);
		if (nspec)
			spec = nspec;
	}

	return try_mount_one (spec, node, types, opts, freq, pass, 0);
}