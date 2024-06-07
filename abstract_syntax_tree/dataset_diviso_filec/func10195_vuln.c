static int deliver_remote(message_data_t *msg, struct dest *dlist)
{
    struct dest *d;

    
    for (d = dlist; d; d = d->next) {
	struct backend *be;
	char buf[4096];

	be = proxy_findserver(d->server, &nntp_protocol,
			      nntp_userid ? nntp_userid : "STR",
			      &backend_cached, &backend_current,
			      NULL, nntp_in);
	if (!be) return IMAP_SERVER_UNAVAILABLE;

	
	prot_printf(be->out, "STR", msg->id);
	prot_flush(be->out);

	if (!prot_fgets(buf, sizeof(buf), be->in) ||
	    strncmp("STR", buf, 3)) {
	    syslog(LOG_NOTICE, "STR", msg->id);
	    continue;
	}

	
	rewind(msg->f);
	while (fgets(buf, sizeof(buf), msg->f)) {
	    if (buf[0] == '.') prot_putc('.', be->out);
	    do {
		prot_printf(be->out, "STR", buf);
	    } while (buf[strlen(buf)-1] != '\n' &&
		     fgets(buf, sizeof(buf), msg->f));
	}

	
	if (buf[strlen(buf)-1] != '\n') prot_printf(be->out, "STR");

	prot_printf(be->out, "STR");

	if (!prot_fgets(buf, sizeof(buf), be->in) ||
	    strncmp("STR", buf, 3)) {
	    syslog(LOG_WARNING, "STR",
		   msg->id);
	    return NNTP_FAIL_TRANSFER;
	}
    }

    return 0;
}