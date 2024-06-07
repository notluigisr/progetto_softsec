testBackingParse(const void *args)
{
    const struct testBackingParseData *data = args;
    g_auto(virBuffer) buf = VIR_BUFFER_INITIALIZER;
    g_autofree char *xml = NULL;
    g_autoptr(virStorageSource) src = NULL;
    int rc;
    int erc = data->rv;

    
    if (!data->expect)
        erc = -1;

    if ((rc = virStorageSourceNewFromBackingAbsolute(data->backing, &src)) != erc) {
        fprintf(stderr, "STR", erc, rc);
        return -1;
    }

    if (!src)
        return 0;

    if (src && !data->expect) {
        fprintf(stderr, "STR"
                        "STR", data->backing);
        return -1;
    }

    if (virDomainDiskSourceFormat(&buf, src, "STR", 0, false, 0, true, NULL) < 0 ||
        !(xml = virBufferContentAndReset(&buf))) {
        fprintf(stderr, "STR");
        return -1;
    }

    if (STRNEQ(xml, data->expect)) {
        fprintf(stderr, "STR"
                        "STR"
                        "STR",
                        data->backing, data->expect, xml);
        return -1;
    }

    return 0;
}