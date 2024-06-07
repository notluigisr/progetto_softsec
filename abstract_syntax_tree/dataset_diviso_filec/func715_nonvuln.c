dissect_kafka_elect_leaders_response_partition(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                                  int offset, kafka_api_version_t api_version)
{

    proto_item *subti;
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_partition,
                                     &subti, "STR");

    offset = dissect_kafka_int32(subtree, hf_kafka_partition_id, tvb, pinfo, offset, NULL);

    offset = dissect_kafka_error(tvb, pinfo, subtree, offset);

    offset = dissect_kafka_string(subtree, hf_kafka_error_message, tvb, pinfo, offset, api_version >= 2, NULL, NULL);

    if (api_version >= 2) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(subti, tvb, offset);

    return offset;
}