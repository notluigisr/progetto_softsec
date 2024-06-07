static int rm_read_extradata(AVFormatContext *s, AVIOContext *pb, AVCodecParameters *par, unsigned size)
{
    if (size >= 1<<24) {
        av_log(s, AV_LOG_ERROR, "STR", size);
        return -1;
    }
    if (ff_get_extradata(s, par, pb, size) < 0)
        return AVERROR(ENOMEM);
    return 0;
}