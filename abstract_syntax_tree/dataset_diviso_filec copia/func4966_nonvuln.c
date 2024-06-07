virDomainRedirdevDefFormat(virBufferPtr buf,
                           virDomainRedirdevDefPtr def,
                           unsigned int flags)
{
    const char *bus;

    bus = virDomainRedirdevBusTypeToString(def->bus);

    virBufferAsprintf(buf, "STR", bus);
    if (virDomainChrAttrsDefFormat(buf, def->source, false) < 0)
        return -1;
    virBufferAddLit(buf, "STR");
    virBufferAdjustIndent(buf, 2);

    if (virDomainChrSourceDefFormat(buf, def->source, flags) < 0)
        return -1;

    if (virDomainDeviceInfoFormat(buf, &def->info,
                                  flags | VIR_DOMAIN_DEF_FORMAT_ALLOW_BOOT) < 0) {
        return -1;
    }
    virBufferAdjustIndent(buf, -2);
    virBufferAddLit(buf, "STR");
    return 0;
}