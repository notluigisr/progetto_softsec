virPCIEDeviceInfoParseXML(xmlXPathContextPtr ctxt,
                          xmlNodePtr pciExpressNode,
                          virPCIEDeviceInfoPtr pci_express)
{
    VIR_XPATH_NODE_AUTORESTORE(ctxt)
    xmlNodePtr lnk;
    int ret = -1;

    ctxt->node = pciExpressNode;

    if ((lnk = virXPathNode("STR", ctxt))) {
        pci_express->link_cap = g_new0(virPCIELink, 1);

        if (virPCIEDeviceInfoLinkParseXML(ctxt, lnk,
                                          pci_express->link_cap) < 0)
            goto cleanup;
    }

    if ((lnk = virXPathNode("STR", ctxt))) {
        pci_express->link_sta = g_new0(virPCIELink, 1);

        if (virPCIEDeviceInfoLinkParseXML(ctxt, lnk,
                                          pci_express->link_sta) < 0)
            goto cleanup;
    }

    ret = 0;
 cleanup:
    return ret;
}