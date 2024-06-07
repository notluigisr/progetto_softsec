static int check_url(HLSContext *c, const char *url) {
    const char *proto_name = avio_find_protocol_name(url);

    if (!proto_name)
        return AVERROR_INVALIDDATA;

    if (av_strstart(proto_name, "STR", NULL)) {
        if (strcmp(c->allowed_extensions, "STR") && !av_match_ext(url, c->allowed_extensions)) {
            av_log(c, AV_LOG_ERROR,
                "STR"
                "STR",
                url);
            return AVERROR_INVALIDDATA;
        }
    } else if (av_strstart(proto_name, "STR", NULL)) {
        ;
    } else
        return AVERROR_INVALIDDATA;

    if (!strncmp(proto_name, url, strlen(proto_name)) && url[strlen(proto_name)] == ':')
        return 0;
    else if (strcmp(proto_name, "STR", 5))
        return AVERROR_INVALIDDATA;

    return 0;
}