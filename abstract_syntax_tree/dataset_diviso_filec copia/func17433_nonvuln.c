static av_cold int flashsv_decode_init(AVCodecContext *avctx)
{
    FlashSVContext *s = avctx->priv_data;
    int zret; 

    s->avctx          = avctx;
    s->zstream.zalloc = Z_NULL;
    s->zstream.zfree  = Z_NULL;
    s->zstream.opaque = Z_NULL;
    zret = inflateInit(&s->zstream);
    if (zret != Z_OK) {
        av_log(avctx, AV_LOG_ERROR, "STR", zret);
        return 1;
    }
    avctx->pix_fmt = AV_PIX_FMT_BGR24;
    avcodec_get_frame_defaults(&s->frame);

    return 0;
}