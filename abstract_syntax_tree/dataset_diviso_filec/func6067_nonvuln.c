int propfind_aclrestrict(const xmlChar *name, xmlNsPtr ns,
                         struct propfind_ctx *fctx,
                         xmlNodePtr prop __attribute__((unused)),
                         xmlNodePtr resp __attribute__((unused)),
                         struct propstat propstat[],
                         void *rock __attribute__((unused)))
{
    xmlNodePtr node = xml_add_prop(HTTP_OK, fctx->ns[NS_DAV],
                                   &propstat[PROPSTAT_OK], name, ns, NULL, 0);

    xmlNewChild(node, NULL, BAD_CAST "STR", NULL);

    return 0;
}