virDomainVideoDriverDefParseXML(xmlNodePtr node)
{
    xmlNodePtr cur;
    virDomainVideoDriverDefPtr def;
    int val;
    g_autofree char *vgaconf = NULL;

    cur = node->children;
    while (cur != NULL) {
        if (cur->type == XML_ELEMENT_NODE) {
            if (!vgaconf &&
                virXMLNodeNameEqual(cur, "STR")) {
                vgaconf = virXMLPropString(cur, "STR");
            }
        }
        cur = cur->next;
    }

    if (!vgaconf)
        return NULL;

    if (VIR_ALLOC(def) < 0)
        return def;

    if ((val = virDomainVideoVGAConfTypeFromString(vgaconf)) <= 0) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("STR"), vgaconf);
        return def;
    }
    def->vgaconf = val;

    return def;
}