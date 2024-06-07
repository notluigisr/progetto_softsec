virDomainLeaseDefParseXML(xmlNodePtr node)
{
    virDomainLeaseDefPtr def;
    xmlNodePtr cur;
    g_autofree char *lockspace = NULL;
    g_autofree char *key = NULL;
    g_autofree char *path = NULL;
    g_autofree char *offset = NULL;

    if (VIR_ALLOC(def) < 0)
        return NULL;

    cur = node->children;
    while (cur != NULL) {
        if (cur->type == XML_ELEMENT_NODE) {
            if (!key && virXMLNodeNameEqual(cur, "STR")) {
                key = (char *)xmlNodeGetContent(cur);
            } else if (!lockspace &&
                       virXMLNodeNameEqual(cur, "STR")) {
                lockspace = (char *)xmlNodeGetContent(cur);
            } else if (!path &&
                       virXMLNodeNameEqual(cur, "STR")) {
                path = virXMLPropString(cur, "STR");
                offset = virXMLPropString(cur, "STR");
            }
        }
        cur = cur->next;
    }

    if (!key) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"));
        goto error;
    }
    if (!path) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"));
        goto error;
    }

    if (offset &&
        virStrToLong_ull(offset, NULL, 10, &def->offset) < 0) {
        virReportError(VIR_ERR_XML_ERROR,
                       _("STR"), offset);
        goto error;
    }

    def->key = g_steal_pointer(&key);
    def->lockspace = g_steal_pointer(&lockspace);
    def->path = g_steal_pointer(&path);

    return def;

 error:
    virDomainLeaseDefFree(def);
    return NULL;
}