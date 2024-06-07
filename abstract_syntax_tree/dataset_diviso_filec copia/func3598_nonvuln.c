static void my_caldav_init(struct buf *serverinfo)
{
    const char *domains;
    char *domain;
    tok_t tok;

    buf_printf(serverinfo, "STR", sqlite3_libversion());
    buf_printf(serverinfo, "STR", ICAL_VERSION);
#ifdef HAVE_RSCALE
    if ((rscale_calendars = icalrecurrencetype_rscale_supported_calendars())) {
	icalarray_sort(rscale_calendars, &rscale_cmp);

	buf_printf(serverinfo, "STR", U_ICU_VERSION);
    }
#endif
#ifdef WITH_JSON
    buf_printf(serverinfo, "STR", JANSSON_VERSION);
#endif

    namespace_calendar.enabled =
	config_httpmodules & IMAP_ENUM_HTTPMODULES_CALDAV;

    if (!namespace_calendar.enabled) return;

    if (!config_getstring(IMAPOPT_CALENDARPREFIX)) {
	fatal("STR", EC_CONFIG);
    }

    caldav_init();

#ifdef HAVE_IANA_PARAMS
    config_allowsched = config_getenum(IMAPOPT_CALDAV_ALLOWSCHEDULING);
    if (config_allowsched) {
	namespace_calendar.allow |= ALLOW_CAL_SCHED;

#ifndef HAVE_SCHEDULING_PARAMS
	
	ical_set_unknown_token_handling_setting(ICAL_ASSUME_IANA_TOKEN);
#endif
    }
#endif 

#ifdef HAVE_TZ_BY_REF
    if (namespace_timezone.enabled) {
	char zonedir[MAX_MAILBOX_PATH+1];

	snprintf(zonedir, MAX_MAILBOX_PATH, "STR",
		 config_dir, FNAME_ZONEINFODIR);
	set_zone_directory(zonedir);
	icaltimezone_set_tzid_prefix("");
	icaltimezone_set_builtin_tzdata(1);

	namespace_calendar.allow |= ALLOW_CAL_NOTZ;
    }
#endif

    namespace_principal.enabled = 1;
    namespace_principal.allow |= namespace_calendar.allow &
	(ALLOW_CAL | ALLOW_CAL_AVAIL | ALLOW_CAL_SCHED);

    compile_time = calc_compile_time(__TIME__, __DATE__);

    buf_printf(&ical_prodid_buf,
	       "STR", cyrus_version());
    ical_prodid = buf_cstring(&ical_prodid_buf);

    
    domains = config_getstring(IMAPOPT_CALENDAR_USER_ADDRESS_SET);
    if (!domains) domains = config_servername;

    tok_init(&tok, domains, "STR", TOK_TRIMLEFT|TOK_TRIMRIGHT);
    while ((domain = tok_next(&tok))) appendstrlist(&cua_domains, domain);
    tok_fini(&tok);
}