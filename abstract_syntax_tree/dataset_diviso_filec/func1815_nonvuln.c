virDomainDefGetVcpusTopology(const virDomainDef *def,
                             unsigned int *maxvcpus)
{
    unsigned long long tmp;

    if (!def->cpu || def->cpu->sockets == 0)
        return 1;

    tmp = def->cpu->sockets;

    
    if ((tmp *= def->cpu->dies) > UINT_MAX ||
        (tmp *= def->cpu->cores) > UINT_MAX ||
        (tmp *= def->cpu->threads) > UINT_MAX) {
        virReportError(VIR_ERR_CONFIG_UNSUPPORTED,
                       _("STR"), UINT_MAX);
        return -1;
    }

    if (maxvcpus)
        *maxvcpus = tmp;

    return 0;
}