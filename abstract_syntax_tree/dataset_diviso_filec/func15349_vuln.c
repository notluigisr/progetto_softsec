void qmp_chardev_remove(const char *id, Error **errp)
{
    CharDriverState *chr;

    chr = qemu_chr_find(id);
    if (chr == NULL) {
        error_setg(errp, "STR", id);
        return;
    }
    if (chr->chr_can_read || chr->chr_read ||
        chr->chr_event || chr->handler_opaque) {
        error_setg(errp, "STR", id);
        return;
    }
    if (chr->replay) {
        error_setg(errp,
            "STR", id);
        return;
    }
    qemu_chr_delete(chr);
}