virDomainVcpuDefPostParse(virDomainDefPtr def)
{
    virDomainVcpuDefPtr vcpu;
    size_t maxvcpus = virDomainDefGetVcpusMax(def);
    size_t i;

    for (i = 0; i < maxvcpus; i++) {
        vcpu = virDomainDefGetVcpu(def, i);

        
        if (!vcpu)
            continue;

        switch (vcpu->hotpluggable) {
        case VIR_TRISTATE_BOOL_ABSENT:
            if (vcpu->online)
                vcpu->hotpluggable = VIR_TRISTATE_BOOL_NO;
            else
                vcpu->hotpluggable = VIR_TRISTATE_BOOL_YES;
            break;

        case VIR_TRISTATE_BOOL_NO:
            if (!vcpu->online) {
                virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                               _("STR"
                                 "STR"), i);
                return -1;
            }
            break;

        case VIR_TRISTATE_BOOL_YES:
        case VIR_TRISTATE_BOOL_LAST:
            break;
        }
    }

    return 0;
}