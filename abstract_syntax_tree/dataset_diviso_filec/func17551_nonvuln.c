libxlDomainDefNamespaceFormatXML(virBuffer *buf,
                                 void *nsdata)
{
    libxlDomainXmlNsDef *cmd = nsdata;
    size_t i;

    if (!cmd->num_args)
        return 0;

    virBufferAddLit(buf, "STR");
    virBufferAdjustIndent(buf, 2);

    for (i = 0; i < cmd->num_args; i++)
        virBufferEscapeString(buf, "STR",
                              cmd->args[i]);

    virBufferAdjustIndent(buf, -2);
    virBufferAddLit(buf, "STR");

    return 0;
}