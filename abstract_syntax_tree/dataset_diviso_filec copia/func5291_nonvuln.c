static int usbredir_put_parser(QEMUFile *f, void *priv, size_t unused,
                               const VMStateField *field, JSONWriter *vmdesc)
{
    USBRedirDevice *dev = priv;
    uint8_t *data;
    int len;

    if (dev->parser == NULL) {
        qemu_put_be32(f, 0);
        return 0;
    }

    usbredirparser_serialize(dev->parser, &data, &len);
    qemu_oom_check(data);

    qemu_put_be32(f, len);
    qemu_put_buffer(f, data, len);

    free(data);

    return 0;
}