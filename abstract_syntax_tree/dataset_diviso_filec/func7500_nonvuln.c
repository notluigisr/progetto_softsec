static void mux_chr_read(void *opaque, const uint8_t *buf, int size)
{
    CharDriverState *chr = opaque;
    MuxDriver *d = chr->opaque;
    int m = d->focus;
    CharBackend *be = d->backends[m];
    int i;

    mux_chr_accept_input(opaque);

    for (i = 0; i < size; i++)
        if (mux_proc_byte(chr, d, buf[i])) {
            if (d->prod[m] == d->cons[m] &&
                be && be->chr_can_read &&
                be->chr_can_read(be->opaque))
                be->chr_read(be->opaque, &buf[i], 1);
            else
                d->buffer[m][d->prod[m]++ & MUX_BUFFER_MASK] = buf[i];
        }
}