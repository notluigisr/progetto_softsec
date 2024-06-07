dissect_kafka_offset_fetch_response(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                    kafka_api_version_t api_version)
{
    proto_item *ti;
    proto_tree *subtree;
    int count = 0;

    if (api_version >= 3) {
        offset = dissect_kafka_throttle_time(tvb, pinfo, tree, offset);
    }

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1, ett_kafka_topics, &ti, "STR");
    offset = dissect_kafka_array(subtree, tvb, pinfo, offset, api_version >= 6, api_version,
                                 &dissect_kafka_offset_fetch_response_topic, &count);
    proto_item_set_end(ti, tvb, offset);
    proto_item_append_text(ti, "STR", count);

    if (api_version >= 2) {
        offset = dissect_kafka_error(tvb, pinfo, tree, offset);
    }

    if (api_version >= 6) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, tree, offset, 0);
    }

    return offset;
}