dissect_kafka_txn_offset_commit_response(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                      kafka_api_version_t api_version)
{
    proto_item *subti;
    proto_tree *subtree;

    offset = dissect_kafka_throttle_time(tvb, pinfo, tree, offset);

    
    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_topics,
                                     &subti, "STR");
    offset = dissect_kafka_array(subtree, tvb, pinfo, offset, api_version >= 3, api_version,
                                 &dissect_kafka_txn_offset_commit_response_topic, NULL);
    proto_item_set_end(subti, tvb, offset);

    if (api_version >= 3) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, tree, offset, 0);
    }

    return offset;
}