virDomainResctrlVcpuMatch(virDomainDefPtr def,
                          virBitmapPtr vcpus,
                          virDomainResctrlDefPtr *resctrl)
{
    ssize_t i = 0;

    for (i = 0; i < def->nresctrls; i++) {
        
        if (virBitmapEqual(def->resctrls[i]->vcpus, vcpus)) {
            *resctrl = def->resctrls[i];
            break;
        }
        if (virBitmapOverlaps(def->resctrls[i]->vcpus, vcpus)) {
            virReportError(VIR_ERR_XML_ERROR, "STR",
                           _("STR"));
            return -1;
        }
    }
    return 0;
}