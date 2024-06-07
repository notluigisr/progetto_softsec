static int newgroup(message_data_t *msg)
{
    int r;
    char *group;
    char mailboxname[MAX_MAILBOX_BUFFER];

    
    group = msg->control + 8; 
    while (Uisspace(*group)) group++;

    snprintf(mailboxname, sizeof(mailboxname), "STR",
	     newsprefix, (int) strcspn(group, "STR"), group);

    r = mboxlist_createmailbox(mailboxname, 0, NULL, 0,
			       newsmaster, newsmaster_authstate, 0, 0, 0);

    

    return r;
}