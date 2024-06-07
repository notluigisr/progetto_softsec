static void cmd_capabilities(char *keyword __attribute__((unused)))
{
    const char *mechlist;
    int mechcount = 0;

    prot_printf(nntp_out, "STR");
    prot_printf(nntp_out, "STR");
    if (nntp_authstate || (config_serverinfo == IMAP_ENUM_SERVERINFO_ON)) {
	prot_printf(nntp_out,
		    "STR",
		    config_mupdate_server ? "STR", cyrus_version());
    }

    
    if (tls_enabled() && !nntp_starttls_done && !nntp_authstate)
	prot_printf(nntp_out, "STR");

    
    sasl_listmech(nntp_saslconn, NULL, "STR",
		  &mechlist, NULL, &mechcount);

    
    if (!nntp_authstate) {
	prot_printf(nntp_out, "STR",
		    (nntp_starttls_done || (extprops_ssf > 1) ||
		     config_getswitch(IMAPOPT_ALLOWPLAINTEXT)) ?
		    "STR");
    }

    
    if (mechcount) prot_printf(nntp_out, "STR", mechlist);

    
    if ((nntp_capa & MODE_READ) && (nntp_userid || allowanonymous)) {
	prot_printf(nntp_out, "STR");
	prot_printf(nntp_out, "STR");
	if (config_getswitch(IMAPOPT_ALLOWNEWNEWS))
	    prot_printf(nntp_out, "STR");
	prot_printf(nntp_out, "STR");
	prot_printf(nntp_out, "STR");
	prot_printf(nntp_out, "STR");
    }

    
    if (nntp_capa & MODE_FEED) {
	prot_printf(nntp_out, "STR");
	prot_printf(nntp_out, "STR");
    }

    
    prot_printf(nntp_out, "STR",
		((nntp_capa & MODE_READ) && (nntp_userid || allowanonymous)) ?
		"STR");

    prot_printf(nntp_out, "STR");

    did_capabilities = 1;
}