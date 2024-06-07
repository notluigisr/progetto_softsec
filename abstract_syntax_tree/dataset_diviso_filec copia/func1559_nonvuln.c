static int caldav_acl(struct transaction_t *txn, xmlNodePtr priv, int *rights)
{
    if (!xmlStrcmp(priv->ns->href, BAD_CAST XML_NS_CALDAV)) {
	
	switch (txn->req_tgt.flags) {
	case TGT_SCHED_INBOX:
	    if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_SCHED;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_INVITE;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_REPLY;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_SCHEDFB;
	    else {
		
		txn->error.precond = DAV_SUPP_PRIV;
	    }
	    break;
	case TGT_SCHED_OUTBOX:
	    if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_SCHED;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_INVITE;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_REPLY;
	    else if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_SCHEDFB;
	    else {
		
		txn->error.precond = DAV_SUPP_PRIV;
	    }
	    break;
	default:
	    if (!xmlStrcmp(priv->name, BAD_CAST "STR"))
		*rights |= DACL_READFB;
	    else {
		
		txn->error.precond = DAV_SUPP_PRIV;
	    }
	    break;
	}

	
	return 1;
    }
    else if (!xmlStrcmp(priv->ns->href, BAD_CAST XML_NS_DAV)) {
	
	if (!xmlStrcmp(priv->name, BAD_CAST "STR")) {
	    switch (txn->req_tgt.flags) {
	    case TGT_SCHED_INBOX:
		
		*rights |= DACL_SCHED;
		break;
	    case TGT_SCHED_OUTBOX:
		
		*rights |= DACL_SCHED;
		break;
	    default:
		
		*rights |= DACL_READFB;
		break;
	    }
	}
	else if (!xmlStrcmp(priv->name, BAD_CAST "STR")) {
	    switch (txn->req_tgt.flags) {
	    case TGT_SCHED_INBOX:
	    case TGT_SCHED_OUTBOX:
		break;
	    default:
		
		*rights |= DACL_READFB;
		break;
	    }
	}
    }

    
    return 0;
}