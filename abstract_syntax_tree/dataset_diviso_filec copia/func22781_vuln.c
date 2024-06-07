static int mux_chr_new_handler_tag(CharDriverState *chr, Error **errp)
{
    MuxDriver *d = chr->opaque;

    if (d->mux_cnt >= MAX_MUX) {
        fprintf(stderr, "STR");
        return -1;
    }

    return d->mux_cnt++;
}