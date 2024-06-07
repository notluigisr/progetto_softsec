virDomainDiskSourceFormatNetworkCookies(virBufferPtr buf,
                                        virStorageSourcePtr src)
{
    g_auto(virBuffer) childBuf = VIR_BUFFER_INIT_CHILD(buf);
    size_t i;

    for (i = 0; i < src->ncookies; i++) {
        virBufferEscapeString(&childBuf, "STR", src->cookies[i]->name);
        virBufferEscapeString(&childBuf, "STR", src->cookies[i]->value);
    }

    virXMLFormatElement(buf, "STR", NULL, &childBuf);
}