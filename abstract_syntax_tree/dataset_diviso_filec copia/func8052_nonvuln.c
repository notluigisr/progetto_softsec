virDomainVideoAccelDefParseXML(xmlNodePtr node)
{
    g_autofree virDomainVideoAccelDefPtr def = NULL;
    int val;
    g_autofree char *accel2d = NULL;
    g_autofree char *accel3d = NULL;
    g_autofree char *rendernode = NULL;

    accel3d = virXMLPropString(node, "STR");
    accel2d = virXMLPropString(node, "STR");
    rendernode = virXMLPropString(node, "STR");

    if (!accel3d && !accel2d && !rendernode) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                       _("STR"));
        return NULL;
    }

    def = g_new0(virDomainVideoAccelDef, 1);

    if (accel3d) {
        if ((val = virTristateBoolTypeFromString(accel3d)) <= 0) {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                           _("STR"), accel3d);
            return NULL;
        }
        def->accel3d = val;
    }

    if (accel2d) {
        if ((val = virTristateBoolTypeFromString(accel2d)) <= 0) {
            virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                           _("STR"), accel2d);
            return NULL;
        }
        def->accel2d = val;
    }

    if (rendernode)
        def->rendernode = virFileSanitizePath(rendernode);

    return g_steal_pointer(&def);
}