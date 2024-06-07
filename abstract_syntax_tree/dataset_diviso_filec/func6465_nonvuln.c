ofputil_decode_table_stats_reply(struct ofpbuf *msg,
                                 struct ofputil_table_stats *stats,
                                 struct ofputil_table_features *features)
{
    const struct ofp_header *oh;

    if (!msg->header) {
        ofpraw_pull_assert(msg);
    }
    oh = msg->header;

    if (!msg->size) {
        return EOF;
    }

    memset(stats, 0, sizeof *stats);
    memset(features, 0, sizeof *features);
    features->supports_eviction = -1;
    features->supports_vacancy_events = -1;

    switch ((enum ofp_version) oh->version) {
    case OFP10_VERSION:
        return ofputil_decode_ofp10_table_stats(msg, stats, features);

    case OFP11_VERSION:
        return ofputil_decode_ofp11_table_stats(msg, stats, features);

    case OFP12_VERSION:
        return ofputil_decode_ofp12_table_stats(msg, stats, features);

    case OFP13_VERSION:
    case OFP14_VERSION:
    case OFP15_VERSION:
    case OFP16_VERSION:
        return ofputil_decode_ofp13_table_stats(msg, stats, features);

    default:
        OVS_NOT_REACHED();
    }
}