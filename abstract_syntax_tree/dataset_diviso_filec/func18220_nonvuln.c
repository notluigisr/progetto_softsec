dissect_kafka_describe_configs_request(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                  kafka_api_version_t api_version)
{
    proto_item *subti;
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_resources,
                                     &subti, "STR");
    offset = dissect_kafka_array(subtree, tvb, pinfo, offset, 0, api_version,
                                 &dissect_kafka_describe_config_request_resource, NULL);

    if (api_version >= 1) {
        proto_tree_add_item(subtree, hf_kafka_config_include_synonyms, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;
    }

    proto_item_set_end(subti, tvb, offset);

    return offset;
}