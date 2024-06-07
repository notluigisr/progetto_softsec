static int parse_timecode_in_framenum_format(AVFormatContext *s, AVStream *st,
                                             int64_t value, int flags)
{
    AVTimecode tc;
    char buf[AV_TIMECODE_STR_SIZE];
    AVRational rate = st->avg_frame_rate;
    int ret = av_timecode_init(&tc, rate, flags, 0, s);
    if (ret < 0)
        return ret;
    av_dict_set(&st->metadata, "STR",
                av_timecode_make_string(&tc, buf, value), 0);
    return 0;
}