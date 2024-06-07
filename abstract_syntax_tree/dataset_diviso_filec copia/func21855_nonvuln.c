static int proppatch_caltransp(xmlNodePtr prop, unsigned set,
			       struct proppatch_ctx *pctx,
			       struct propstat propstat[],
			       void *rock __attribute__((unused)))
{
    int r;

    if (pctx->req_tgt->collection && !pctx->req_tgt->resource) {
	const char *prop_annot =
	    ANNOT_NS "STR";
	annotate_state_t *astate = NULL;
	buf_reset(&pctx->buf);

	if (set) {
	    xmlNodePtr cur;

	    
	    for (cur = prop->children; cur; cur = cur->next) {

		
		if (cur->type != XML_ELEMENT_NODE) continue;
		if (!xmlStrcmp(cur->name, BAD_CAST "STR") ||
		    !xmlStrcmp(cur->name, BAD_CAST "STR")) {
		    buf_setcstr(&pctx->buf, (const char *)cur->name);
		    break;
		}
		else {
		    
		    xml_add_prop(HTTP_CONFLICT, pctx->ns[NS_DAV],
				 &propstat[PROPSTAT_CONFLICT],
				 prop->name, prop->ns, NULL, 0);

		    *pctx->ret = HTTP_FORBIDDEN;

		    return 0;
		}
	    }
	}

	r = mailbox_get_annotate_state(pctx->mailbox, 0, &astate);
	if (!r) r = annotate_state_writemask(astate, prop_annot, httpd_userid, &pctx->buf);
	if (!r) {
	    xml_add_prop(HTTP_OK, pctx->ns[NS_DAV],
			 &propstat[PROPSTAT_OK], prop->name, prop->ns, NULL, 0);
	}
	else {
	    xml_add_prop(HTTP_SERVER_ERROR, pctx->ns[NS_DAV],
			 &propstat[PROPSTAT_ERROR],
			 prop->name, prop->ns, NULL, 0);
	}
    }
    else {
	xml_add_prop(HTTP_FORBIDDEN, pctx->ns[NS_DAV],
		     &propstat[PROPSTAT_FORBID],
		     prop->name, prop->ns, NULL, 0);

	*pctx->ret = HTTP_FORBIDDEN;
    }

    return 0;
}