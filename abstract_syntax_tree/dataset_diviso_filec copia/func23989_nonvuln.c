virDomainDefPostParseMemory(virDomainDefPtr def,
                            unsigned int parseFlags)
{
    size_t i;
    unsigned long long numaMemory = 0;
    unsigned long long hotplugMemory = 0;

    
    if (def->mem.total_memory == 0 ||
        parseFlags & VIR_DOMAIN_DEF_PARSE_ABI_UPDATE ||
        parseFlags & VIR_DOMAIN_DEF_PARSE_ABI_UPDATE_MIGRATION)
        numaMemory = virDomainNumaGetMemorySize(def->numa);

    
    for (i = 0; i < def->nmems; i++)
        hotplugMemory += def->mems[i]->size;

    if (numaMemory) {
        
        virDomainDefSetMemoryTotal(def, numaMemory + hotplugMemory);
    } else {
        
        if (hotplugMemory > def->mem.total_memory) {
            virReportError(VIR_ERR_XML_ERROR, "STR",
                           _("STR"
                             "STR"));
            return -1;
        }
    }

    if (virDomainDefGetMemoryInitial(def) == 0) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"
                         "STR"));
        return -1;
    }

    if (def->mem.cur_balloon > virDomainDefGetMemoryTotal(def) ||
        def->mem.cur_balloon == 0)
        def->mem.cur_balloon = virDomainDefGetMemoryTotal(def);

    if ((def->mem.max_memory || def->mem.memory_slots) &&
        !(def->mem.max_memory && def->mem.memory_slots)) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"
                         "STR"));
        return -1;
    }

    if (def->mem.max_memory &&
        def->mem.max_memory < virDomainDefGetMemoryTotal(def)) {
        virReportError(VIR_ERR_XML_ERROR, "STR",
                       _("STR"
                         "STR"));
        return -1;
    }

    return 0;
}