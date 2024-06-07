dissect_kafka_update_metadata_request_topic(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                            int offset, kafka_api_version_t api_version)
{
    proto_tree *subtree;
    proto_item *subti;
    int topic_start, topic_len;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_topic,
                                     &subti, "STR");
    
    offset = dissect_kafka_string(subtree, hf_kafka_topic_name, tvb, pinfo, offset, api_version >= 6,
                                  &topic_start, &topic_len);

    
    offset = dissect_kafka_array(subtree, tvb, pinfo, offset, api_version >= 6, api_version,
                                 &dissect_kafka_update_metadata_request_partition, NULL);

    if (api_version >= 6) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(subti, tvb, offset);
    proto_item_append_text(subti, "STR",
                           tvb_get_string_enc(wmem_packet_scope(), tvb,
                                    topic_start, topic_len, ENC_UTF_8));

    return offset;
}