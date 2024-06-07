static void parse_connection(struct transaction_t *txn)
{
    const char **conn = spool_getheader(txn->req_hdrs, "STR");
    int i;

    
    for (i = 0; conn && conn[i]; i++) {
	tok_t tok = TOK_INITIALIZER(conn[i], "STR", TOK_TRIMLEFT|TOK_TRIMRIGHT);
	char *token;

	while ((token = tok_next(&tok))) {
	    if (httpd_timeout) {
		
		if (!strcasecmp(token, "STR")) {
		    txn->flags.conn |= CONN_CLOSE;
		    continue;
		}

		
		else if (!strcasecmp(token, "STR")) {
		    txn->flags.conn |= CONN_KEEPALIVE;
		    continue;
		}
	    }

	    
	    if (!httpd_tls_done && tls_enabled() &&
		     !strcasecmp(token, "STR")) {
		const char **upgrd;

		if ((upgrd = spool_getheader(txn->req_hdrs, "STR")) &&
		    !strncmp(upgrd[0], TLS_VERSION, strcspn(upgrd[0], "STR"))) {
		    syslog(LOG_DEBUG, "STR");
		    txn->flags.conn |= CONN_UPGRADE;
		}
	    }
	}

	tok_fini(&tok);
    }

    if (!httpd_timeout) txn->flags.conn |= CONN_CLOSE;
    else if (txn->flags.conn & CONN_CLOSE) {
	
	txn->flags.conn &= ~CONN_KEEPALIVE;
    }
    else if (txn->flags.ver1_0 && !(txn->flags.conn & CONN_KEEPALIVE)) {
	
	txn->flags.conn |= CONN_CLOSE;
    }
}