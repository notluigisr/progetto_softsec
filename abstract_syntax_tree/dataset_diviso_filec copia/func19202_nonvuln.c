int qemu_chr_fe_write_all(CharBackend *be, const uint8_t *buf, int len)
{
    CharDriverState *s = be->chr;

    if (!s) {
        return 0;
    }

    return qemu_chr_write_all(s, buf, len);
}