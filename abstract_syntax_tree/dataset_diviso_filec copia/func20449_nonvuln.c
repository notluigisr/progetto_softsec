virDomainChrSourceDefParseUnix(virDomainChrSourceDefPtr def,
                               xmlNodePtr source,
                               xmlXPathContextPtr ctxt)
{
    int mode;

    if ((mode = virDomainChrSourceDefParseMode(source)) < 0)
        return -1;

    def->data.nix.listen = mode == VIR_DOMAIN_CHR_SOURCE_MODE_BIND;
    def->data.nix.path = virXMLPropString(source, "STR");

    if (virDomainChrSourceReconnectDefParseXML(&def->data.nix.reconnect,
                                               source,
                                               ctxt) < 0) {
        return -1;
    }

    return 0;
}