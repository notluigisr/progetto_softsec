static int propfind_tzservset(const xmlChar *name, xmlNsPtr ns,
			      struct propfind_ctx *fctx,
			      xmlNodePtr resp __attribute__((unused)),
			      struct propstat propstat[],
			      void *rock __attribute__((unused)))
{
    assert(name && ns && fctx && propstat);

#ifdef HAVE_TZ_BY_REF
    if (fctx->req_tgt->resource) return HTTP_NOT_FOUND;

    if (namespace_calendar.allow & ALLOW_CAL_NOTZ) {
	xmlNodePtr node;
	const char *proto = NULL, *host = NULL;

	node = xml_add_prop(HTTP_OK, fctx->ns[NS_DAV], &propstat[PROPSTAT_OK],
			    name, ns, NULL, 0);

	http_proto_host(fctx->req_hdrs, &proto, &host);

	buf_reset(&fctx->buf);
	buf_printf(&fctx->buf, "STR",
		   proto, host, namespace_timezone.prefix);

	xml_add_href(node, fctx->ns[NS_DAV], buf_cstring(&fctx->buf));

	return 0;
    }
#endif 

    return HTTP_NOT_FOUND;
}