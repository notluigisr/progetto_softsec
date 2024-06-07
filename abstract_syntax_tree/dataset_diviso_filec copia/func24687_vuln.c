static av_cold int decode_init(AVCodecContext *avctx)
{
    UtvideoContext * const c = avctx->priv_data;

    c->avctx = avctx;

    ff_bswapdsp_init(&c->bdsp);

    if (avctx->extradata_size < 16) {
        av_log(avctx, AV_LOG_ERROR,
               "STR",
               avctx->extradata_size);
        return AVERROR_INVALIDDATA;
    }

    av_log(avctx, AV_LOG_DEBUG, "STR",
           avctx->extradata[3], avctx->extradata[2],
           avctx->extradata[1], avctx->extradata[0]);
    av_log(avctx, AV_LOG_DEBUG, "STR",
           AV_RB32(avctx->extradata + 4));
    c->frame_info_size = AV_RL32(avctx->extradata + 8);
    c->flags           = AV_RL32(avctx->extradata + 12);

    if (c->frame_info_size != 4)
        avpriv_request_sample(avctx, "STR");
    av_log(avctx, AV_LOG_DEBUG, "STR", c->flags);
    c->slices      = (c->flags >> 24) + 1;
    c->compression = c->flags & 1;
    c->interlaced  = c->flags & 0x800;

    c->slice_bits_size = 0;

    switch (avctx->codec_tag) {
    case MKTAG('U', 'L', 'R', 'G'):
        c->planes      = 3;
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
        break;
    case MKTAG('U', 'L', 'R', 'A'):
        c->planes      = 4;
        avctx->pix_fmt = AV_PIX_FMT_RGBA;
        break;
    case MKTAG('U', 'L', 'Y', '0'):
        c->planes      = 3;
        avctx->pix_fmt = AV_PIX_FMT_YUV420P;
        avctx->colorspace = AVCOL_SPC_BT470BG;
        break;
    case MKTAG('U', 'L', 'Y', '2'):
        c->planes      = 3;
        avctx->pix_fmt = AV_PIX_FMT_YUV422P;
        avctx->colorspace = AVCOL_SPC_BT470BG;
        break;
    case MKTAG('U', 'L', 'H', '0'):
        c->planes      = 3;
        avctx->pix_fmt = AV_PIX_FMT_YUV420P;
        avctx->colorspace = AVCOL_SPC_BT709;
        break;
    case MKTAG('U', 'L', 'H', '2'):
        c->planes      = 3;
        avctx->pix_fmt = AV_PIX_FMT_YUV422P;
        avctx->colorspace = AVCOL_SPC_BT709;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "STR",
               avctx->codec_tag);
        return AVERROR_INVALIDDATA;
    }

    return 0;
}