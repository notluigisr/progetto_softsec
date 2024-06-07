dissect_kafka_create_partitions_request_topic(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                              int offset, kafka_api_version_t api_version)
{
    proto_item *subti, *subsubti;
    proto_tree *subtree, *subsubtree;
    int topic_start, topic_len;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1, ett_kafka_resource, &subti, "STR");

    offset = dissect_kafka_string(subtree, hf_kafka_topic_name, tvb, pinfo, offset, api_version >= 2, &topic_start, &topic_len);

    proto_tree_add_item(subtree, hf_kafka_partition_count, tvb, offset, 4, ENC_BIG_ENDIAN);
    offset += 4;

    subsubtree = proto_tree_add_subtree(subtree, tvb, offset, -1, ett_kafka_brokers, &subsubti, "STR");
    offset = dissect_kafka_array(subsubtree, tvb, pinfo, offset, api_version >= 2, api_version,
                                 &dissect_kafka_create_partitions_request_broker, NULL);
    proto_item_set_end(subsubti, tvb, offset);

    if (api_version >= 2) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(subti, tvb, offset);
    proto_item_append_text(subti, "STR",
                           tvb_get_string_enc(wmem_packet_scope(), tvb,
                                              topic_start, topic_len, ENC_UTF_8));

    return offset;
}