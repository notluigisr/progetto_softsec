virDomainDefSave(virDomainDefPtr def,
                 virDomainXMLOptionPtr xmlopt,
                 const char *configDir)
{
    g_autofree char *xml = NULL;

    if (!(xml = virDomainDefFormat(def, xmlopt, VIR_DOMAIN_DEF_FORMAT_SECURE)))
        return -1;

    return virDomainDefSaveXML(def, configDir, xml);
}