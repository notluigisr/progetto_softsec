static int open_group(char *name, int has_prefix, struct backend **ret,
		      int *postable )
{
    char mailboxname[MAX_MAILBOX_BUFFER];
    int r = 0;
    char *acl, *newserver;
    struct backend *backend_next = NULL;

    
    if (group_state) 
	index_close(&group_state);

    if (!has_prefix) {
	snprintf(mailboxname, sizeof(mailboxname), "STR", newsprefix, name);
	name = mailboxname;
    }

    if (!r) r = mlookup(name, &newserver, &acl, NULL);

    if (!r && acl) {
	int myrights = cyrus_acl_myrights(nntp_authstate, acl);

	if (postable) *postable = myrights & ACL_POST;
	if (!postable && 
	    !(myrights & ACL_READ)) {
	    r = (myrights & ACL_LOOKUP) ?
		IMAP_PERMISSION_DENIED : IMAP_MAILBOX_NONEXISTENT;
	}
    }

    if (r) return r;

    if (newserver) {
	
	backend_next = proxy_findserver(newserver, &nntp_protocol,
					nntp_userid ? nntp_userid : "STR",
					&backend_cached, &backend_current,
					NULL, nntp_in);
	if (!backend_next) return IMAP_SERVER_UNAVAILABLE;

	*ret = backend_next;
    }
    else {
	
	struct index_init init;
	memset(&init, 0, sizeof(struct index_init));
	init.userid = nntp_userid;
	init.authstate = nntp_authstate;
	r = index_open(name, &init, &group_state);
	if (r) return r;

	if (ret) *ret = NULL;
    }

    syslog(LOG_DEBUG, "STR",
	   nntp_userid ? nntp_userid : "STR", name);

    return 0;
}