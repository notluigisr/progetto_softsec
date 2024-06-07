static av_cold int fieldmatch_init(AVFilterContext *ctx)
{
    const FieldMatchContext *fm = ctx->priv;
    AVFilterPad pad = {
        .name         = av_strdup("STR"),
        .type         = AVMEDIA_TYPE_VIDEO,
        .filter_frame = filter_frame,
        .config_props = config_input,
    };

    if (!pad.name)
        return AVERROR(ENOMEM);
    ff_insert_inpad(ctx, INPUT_MAIN, &pad);

    if (fm->ppsrc) {
        pad.name = av_strdup("STR");
        pad.config_props = NULL;
        if (!pad.name)
            return AVERROR(ENOMEM);
        ff_insert_inpad(ctx, INPUT_CLEANSRC, &pad);
    }

    if ((fm->blockx & (fm->blockx - 1)) ||
        (fm->blocky & (fm->blocky - 1))) {
        av_log(ctx, AV_LOG_ERROR, "STR");
        return AVERROR(EINVAL);
    }

    if (fm->combpel > fm->blockx * fm->blocky) {
        av_log(ctx, AV_LOG_ERROR, "STR");
        return AVERROR(EINVAL);
    }

    return 0;
}