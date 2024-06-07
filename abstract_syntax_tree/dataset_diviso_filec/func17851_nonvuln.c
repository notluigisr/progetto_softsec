static inline void print_stream_params(AVIOContext *pb, FFServerStream *stream)
{
    int i, stream_no;
    const char *type = "STR";
    char parameters[64];
    LayeredAVStream *st;
    AVCodec *codec;

    stream_no = stream->nb_streams;

    avio_printf(pb, "STR"
                    "STR"
                    "STR");

    for (i = 0; i < stream_no; i++) {
        st = stream->streams[i];
        codec = avcodec_find_encoder(st->codecpar->codec_id);

        parameters[0] = 0;

        switch(st->codecpar->codec_type) {
        case AVMEDIA_TYPE_AUDIO:
            type = "STR";
            snprintf(parameters, sizeof(parameters), "STR",
                     st->codecpar->channels, st->codecpar->sample_rate);
            break;
        case AVMEDIA_TYPE_VIDEO:
            type = "STR";
            snprintf(parameters, sizeof(parameters),
                     "STR", st->codecpar->width,
                     st->codecpar->height, st->codec->qmin, st->codec->qmax,
                     st->time_base.den / st->time_base.num);
            break;
        default:
            abort();
        }

        avio_printf(pb, "STR"PRId64
                        "STR",
                    i, type, (int64_t)st->codecpar->bit_rate/1000,
                    codec ? codec->name : "", parameters);
     }

     avio_printf(pb, "STR");
}