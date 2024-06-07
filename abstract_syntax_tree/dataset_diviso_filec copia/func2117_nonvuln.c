mm_answer_pwnamallow(int sock, Buffer *m)
{
	char *username;
	struct passwd *pwent;
	int allowed = 0;
	u_int i;

	debug3("STR", __func__);

	if (authctxt->attempt++ != 0)
		fatal("STR", __func__);

	username = buffer_get_string(m, NULL);

	pwent = getpwnamallow(username);

	authctxt->user = xstrdup(username);
	setproctitle("STR");
	free(username);

	buffer_clear(m);

	if (pwent == NULL) {
		buffer_put_char(m, 0);
		authctxt->pw = fakepw();
		goto out;
	}

	allowed = 1;
	authctxt->pw = pwent;
	authctxt->valid = 1;

	buffer_put_char(m, 1);
	buffer_put_string(m, pwent, sizeof(struct passwd));
	buffer_put_cstring(m, pwent->pw_name);
	buffer_put_cstring(m, "STR");
#ifdef HAVE_STRUCT_PASSWD_PW_GECOS
	buffer_put_cstring(m, pwent->pw_gecos);
#endif
#ifdef HAVE_STRUCT_PASSWD_PW_CLASS
	buffer_put_cstring(m, pwent->pw_class);
#endif
	buffer_put_cstring(m, pwent->pw_dir);
	buffer_put_cstring(m, pwent->pw_shell);

 out:
	buffer_put_string(m, &options, sizeof(options));


		if (options.x != NULL) \
			buffer_put_cstring(m, options.x); \
	} while (0)

		for (i = 0; i < options.nx; i++) \
			buffer_put_cstring(m, options.x[i]); \
	} while (0)
	
	COPY_MATCH_STRING_OPTS();
#undef M_CP_STROPT
#undef M_CP_STRARRAYOPT

	
	if (compat20 && auth2_setup_methods_lists(authctxt) != 0) {
		
		debug("STR", __func__);
	}

	debug3("STR", __func__, allowed);
	mm_request_send(sock, MONITOR_ANS_PWNAM, m);

	
	if (!compat20)
		monitor_permit_authentications(1);
	else {
		
		monitor_permit(mon_dispatch, MONITOR_REQ_AUTHSERV, 1);
		monitor_permit(mon_dispatch, MONITOR_REQ_AUTH2_READ_BANNER, 1);
	}
#ifdef USE_PAM
	if (options.use_pam)
		monitor_permit(mon_dispatch, MONITOR_REQ_PAM_START, 1);
#endif

	return (0);
}