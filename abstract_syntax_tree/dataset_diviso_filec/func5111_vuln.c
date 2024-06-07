virDomainDiskSourceFormatNetwork(virBufferPtr attrBuf,
                                 virBufferPtr childBuf,
                                 virStorageSourcePtr src,
                                 unsigned int flags)
{
    size_t n;
    g_autofree char *path = NULL;

    virBufferAsprintf(attrBuf, "STR",
                      virStorageNetProtocolTypeToString(src->protocol));

    if (src->volume)
        path = g_strdup_printf("STR", src->volume, src->path);

    virBufferEscapeString(attrBuf, "STR", path ? path : src->path);
    virBufferEscapeString(attrBuf, "STR", src->query);

    if (src->haveTLS != VIR_TRISTATE_BOOL_ABSENT &&
        !(flags & VIR_DOMAIN_DEF_FORMAT_MIGRATABLE &&
          src->tlsFromConfig))
        virBufferAsprintf(attrBuf, "STR",
                          virTristateBoolTypeToString(src->haveTLS));
    if (flags & VIR_DOMAIN_DEF_FORMAT_STATUS)
        virBufferAsprintf(attrBuf, "STR", src->tlsFromConfig);

    for (n = 0; n < src->nhosts; n++) {
        virBufferAddLit(childBuf, "STR");
        virBufferEscapeString(childBuf, "STR", src->hosts[n].name);

        if (src->hosts[n].port)
            virBufferAsprintf(childBuf, "STR", src->hosts[n].port);

        if (src->hosts[n].transport)
            virBufferAsprintf(childBuf, "STR",
                              virStorageNetHostTransportTypeToString(src->hosts[n].transport));

        virBufferEscapeString(childBuf, "STR", src->hosts[n].socket);
        virBufferAddLit(childBuf, "STR");
    }

    virBufferEscapeString(childBuf, "STR", src->snapshot);
    virBufferEscapeString(childBuf, "STR", src->configFile);

    virStorageSourceInitiatorFormatXML(&src->initiator, childBuf);

    if (src->sslverify != VIR_TRISTATE_BOOL_ABSENT) {
        virBufferAsprintf(childBuf, "STR",
                          virTristateBoolTypeToString(src->sslverify));
    }

    virDomainDiskSourceFormatNetworkCookies(childBuf, src);

    if (src->readahead)
        virBufferAsprintf(childBuf, "STR", src->readahead);

    if (src->timeout)
        virBufferAsprintf(childBuf, "STR", src->timeout);

    return 0;
}