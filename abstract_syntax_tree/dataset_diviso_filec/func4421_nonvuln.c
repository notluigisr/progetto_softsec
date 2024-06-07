virDomainGraphicsDefParseXML(virDomainXMLOptionPtr xmlopt,
                             xmlNodePtr node,
                             xmlXPathContextPtr ctxt,
                             unsigned int flags)
{
    virDomainGraphicsDefPtr def;
    int typeVal;
    g_autofree char *type = NULL;

    if (!(def = virDomainGraphicsDefNew(xmlopt)))
        return NULL;

    type = virXMLPropString(node, "STR");
    if (!type) {
        virReportError(VIR_ERR_INTERNAL_ERROR,
                       "STR"));
        goto error;
    }

    if ((typeVal = virDomainGraphicsTypeFromString(type)) < 0) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("STR"), type);
        goto error;
    }
    def->type = typeVal;

    switch (def->type) {
    case VIR_DOMAIN_GRAPHICS_TYPE_VNC:
        if (virDomainGraphicsDefParseXMLVNC(def, node, ctxt, flags) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_SDL:
        if (virDomainGraphicsDefParseXMLSDL(def, node, ctxt) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_RDP:
        if (virDomainGraphicsDefParseXMLRDP(def, node, ctxt, flags) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_DESKTOP:
        if (virDomainGraphicsDefParseXMLDesktop(def, node) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_SPICE:
        if (virDomainGraphicsDefParseXMLSpice(def, node, ctxt, flags) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_EGL_HEADLESS:
        if (virDomainGraphicsDefParseXMLEGLHeadless(def, node, ctxt) < 0)
            goto error;
        break;
    case VIR_DOMAIN_GRAPHICS_TYPE_LAST:
        break;
    }

    return def;

 error:
    virDomainGraphicsDefFree(def);
    def = NULL;
    return NULL;
}