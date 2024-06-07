ofputil_decode_ofp15_group_desc_reply(struct ofputil_group_desc *gd,
                                      struct ofpbuf *msg,
                                      enum ofp_version version)
{
    struct ofp15_group_desc_stats *ogds;
    uint16_t length, bucket_list_len;
    int error;

    if (!msg->header) {
        ofpraw_pull_assert(msg);
    }

    if (!msg->size) {
        return EOF;
    }

    ogds = ofpbuf_try_pull(msg, sizeof *ogds);
    if (!ogds) {
        VLOG_WARN_RL(&bad_ofmsg_rl, "STR"
                     "STR", msg->size);
        return OFPERR_OFPBRC_BAD_LEN;
    }
    gd->type = ogds->type;
    gd->group_id = ntohl(ogds->group_id);

    length = ntohs(ogds->length);
    if (length < sizeof *ogds || length - sizeof *ogds > msg->size) {
        VLOG_WARN_RL(&bad_ofmsg_rl, "STR"
                     "STR", length);
        return OFPERR_OFPBRC_BAD_LEN;
    }

    bucket_list_len = ntohs(ogds->bucket_list_len);
    if (length < bucket_list_len + sizeof *ogds) {
        VLOG_WARN_RL(&bad_ofmsg_rl, "STR"
                     "STR", bucket_list_len);
        return OFPERR_OFPBRC_BAD_LEN;
    }
    error = ofputil_pull_ofp15_buckets(msg, bucket_list_len, version, gd->type,
                                       &gd->buckets);
    if (error) {
        return error;
    }

    
    return parse_ofp15_group_properties(msg, gd->type, OFPGC15_ADD, &gd->props,
                                        length - sizeof *ogds - bucket_list_len);
}