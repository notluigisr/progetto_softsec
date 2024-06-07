static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext   *ctx     = inlink->dst;
    FieldOrderContext *s       = ctx->priv;
    AVFilterLink      *outlink = ctx->outputs[0];
    int h, plane, line_step, line_size, line;
    uint8_t *data;

    if (!frame->interlaced_frame ||
        frame->top_field_first == s->dst_tff)
        return ff_filter_frame(outlink, frame);

    av_dlog(ctx,
            "STR",
            s->dst_tff ? "STR");
    h = frame->height;
    for (plane = 0; plane < 4 && frame->data[plane]; plane++) {
        line_step = frame->linesize[plane];
        line_size = s->line_size[plane];
        data = frame->data[plane];
        if (s->dst_tff) {
            
            for (line = 0; line < h; line++) {
                if (1 + line < frame->height) {
                    memcpy(data, data + line_step, line_size);
                } else {
                    memcpy(data, data - line_step - line_step, line_size);
                }
                data += line_step;
            }
        } else {
            
            data += (h - 1) * line_step;
            for (line = h - 1; line >= 0 ; line--) {
                if (line > 0) {
                    memcpy(data, data - line_step, line_size);
                } else {
                    memcpy(data, data + line_step + line_step, line_size);
                }
                data -= line_step;
            }
        }
    }
    frame->top_field_first = s->dst_tff;

    return ff_filter_frame(outlink, frame);
}