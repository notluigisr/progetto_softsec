static int h264_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    H264Context *h     = avctx->priv_data;
    AVFrame *pict      = data;
    int buf_index      = 0;
    int ret;

    h->flags = avctx->flags;

    
out:
    if (buf_size == 0) {
        Picture *out;
        int i, out_idx;

        h->cur_pic_ptr = NULL;

        
        out     = h->delayed_pic[0];
        out_idx = 0;
        for (i = 1;
             h->delayed_pic[i] &&
             !h->delayed_pic[i]->f.key_frame &&
             !h->delayed_pic[i]->mmco_reset;
             i++)
            if (h->delayed_pic[i]->poc < out->poc) {
                out     = h->delayed_pic[i];
                out_idx = i;
            }

        for (i = out_idx; h->delayed_pic[i]; i++)
            h->delayed_pic[i] = h->delayed_pic[i + 1];

        if (out) {
            ret = output_frame(h, pict, &out->f);
            if (ret < 0)
                return ret;
            *got_frame = 1;
        }

        return buf_index;
    }

    buf_index = decode_nal_units(h, buf, buf_size, 0);
    if (buf_index < 0)
        return AVERROR_INVALIDDATA;

    if (!h->cur_pic_ptr && h->nal_unit_type == NAL_END_SEQUENCE) {
        buf_size = 0;
        goto out;
    }

    if (!(avctx->flags2 & CODEC_FLAG2_CHUNKS) && !h->cur_pic_ptr) {
        if (avctx->skip_frame >= AVDISCARD_NONREF)
            return 0;
        av_log(avctx, AV_LOG_ERROR, "STR");
        return AVERROR_INVALIDDATA;
    }

    if (!(avctx->flags2 & CODEC_FLAG2_CHUNKS) ||
        (h->mb_y >= h->mb_height && h->mb_height)) {
        if (avctx->flags2 & CODEC_FLAG2_CHUNKS)
            decode_postinit(h, 1);

        field_end(h, 0);

        *got_frame = 0;
        if (h->next_output_pic && ((avctx->flags & CODEC_FLAG_OUTPUT_CORRUPT) ||
                                   h->next_output_pic->recovered)) {
            if (!h->next_output_pic->recovered)
                h->next_output_pic->f.flags |= AV_FRAME_FLAG_CORRUPT;

            ret = output_frame(h, pict, &h->next_output_pic->f);
            if (ret < 0)
                return ret;
            *got_frame = 1;
        }
    }

    assert(pict->buf[0] || !*got_frame);

    return get_consumed_bytes(buf_index, buf_size);
}