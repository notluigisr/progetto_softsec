static GSource *fd_chr_add_watch(CharDriverState *chr, GIOCondition cond)
{
    FDCharDriver *s = chr->opaque;
    return qio_channel_create_watch(s->ioc_out, cond);
}