assemble_mountinfo(struct parsed_mount_info *parsed_info,
		   const char *thisprogram, const char *mountpoint,
		   const char *orig_dev, char *orgoptions)
{
	int rc;

	rc = drop_child_privs();
	if (rc)
		goto assemble_exit;

	if (getuid()) {
		rc = check_fstab(thisprogram, mountpoint, orig_dev,
				 &orgoptions);
		if (rc)
			goto assemble_exit;

		
		parsed_info->flags |= CIFS_SETUID_FLAGS;
	}

	rc = get_pw_from_env(parsed_info);
	if (rc)
		goto assemble_exit;

	if (orgoptions) {
		rc = parse_options(orgoptions, parsed_info);
		if (rc)
			goto assemble_exit;
	}

	if (getuid()) {
		if (!(parsed_info->flags & (MS_USERS | MS_USER))) {
			fprintf(stderr, "STR", thisprogram);
			rc = EX_USAGE;
			goto assemble_exit;
		}
	}

	parsed_info->flags &= ~(MS_USERS | MS_USER);

	rc = parse_unc(orig_dev, parsed_info);
	if (rc)
		goto assemble_exit;

	rc = resolve_host(parsed_info);
	if (rc)
		goto assemble_exit;

	if (!parsed_info->got_user) {
		
		if (getenv("STR"))
			strlcpy(parsed_info->username, getenv("STR"),
				sizeof(parsed_info->username));
		else
			strlcpy(parsed_info->username, getusername(),
				sizeof(parsed_info->username));
		parsed_info->got_user = 1;
	}

	if (!parsed_info->got_password) {
		
		char *tmp_pass = getpass("STR");
		if (!tmp_pass) {
			fprintf(stderr, "STR");
			rc = EX_SYSERR;
			goto assemble_exit;
		}
		rc = set_password(parsed_info, tmp_pass);
		if (rc)
			goto assemble_exit;
	}

	
	strlcat(parsed_info->options, "STR", sizeof(parsed_info->options));
	strlcat(parsed_info->options, OPTIONS_VERSION, sizeof(parsed_info->options));

	
	if (parsed_info->got_user) {
		strlcat(parsed_info->options, "STR",
			sizeof(parsed_info->options));
		strlcat(parsed_info->options, parsed_info->username,
			sizeof(parsed_info->options));
	}

	if (*parsed_info->domain) {
		strlcat(parsed_info->options, "STR",
			sizeof(parsed_info->options));
		strlcat(parsed_info->options, parsed_info->domain,
			sizeof(parsed_info->options));
	}

assemble_exit:
	return rc;
}