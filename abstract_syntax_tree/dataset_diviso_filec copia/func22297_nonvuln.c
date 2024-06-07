virDomainBlkioDeviceParseXML(xmlNodePtr root,
                             virBlkioDevicePtr dev)
{
    xmlNodePtr node;
    g_autofree char *c = NULL;

    node = root->children;
    while (node) {
        if (node->type == XML_ELEMENT_NODE) {
            if (virXMLNodeNameEqual(node, "STR") && !dev->path) {
                dev->path = (char *)xmlNodeGetContent(node);
            } else if (virXMLNodeNameEqual(node, "STR")) {
                c = (char *)xmlNodeGetContent(node);
                if (virStrToLong_ui(c, NULL, 10, &dev->weight) < 0) {
                    virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                                   _("STR"),
                                   c);
                        goto error;
                }
                VIR_FREE(c);
            } else if (virXMLNodeNameEqual(node, "STR")) {
                c = (char *)xmlNodeGetContent(node);
                if (virStrToLong_ull(c, NULL, 10, &dev->rbps) < 0) {
                    virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                                   _("STR"),
                                   c);
                    goto error;
                }
                VIR_FREE(c);
            } else if (virXMLNodeNameEqual(node, "STR")) {
                c = (char *)xmlNodeGetContent(node);
                if (virStrToLong_ull(c, NULL, 10, &dev->wbps) < 0) {
                    virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                                   _("STR"),
                                   c);
                    goto error;
                }
                VIR_FREE(c);
            } else if (virXMLNodeNameEqual(node, "STR")) {
                c = (char *)xmlNodeGetContent(node);
                if (virStrToLong_ui(c, NULL, 10, &dev->riops) < 0) {
                    virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                                   _("STR"),
                                   c);
                    goto error;
                }
                VIR_FREE(c);
            } else if (virXMLNodeNameEqual(node, "STR")) {
                c = (char *)xmlNodeGetContent(node);
                if (virStrToLong_ui(c, NULL, 10, &dev->wiops) < 0) {
                    virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                                   _("STR"),
                                   c);
                    goto error;
                }
                VIR_FREE(c);
            }
        }
        node = node->next;
    }
    if (!dev->path) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED, "STR",
                       _("STR"));
        return -1;
    }

    return 0;

 error:
    VIR_FREE(dev->path);
    return -1;
}