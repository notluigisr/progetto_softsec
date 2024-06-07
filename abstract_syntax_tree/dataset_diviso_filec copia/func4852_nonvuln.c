dissect_kafka_create_delegation_token_request_renewer(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                              int offset, kafka_api_version_t api_version)
{
    proto_item *subti;
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1, ett_kafka_renewer, &subti, "STR");

    offset = dissect_kafka_string(subtree, hf_kafka_token_principal_type, tvb, pinfo, offset, api_version >= 2, NULL, NULL);

    offset = dissect_kafka_string(subtree, hf_kafka_token_principal_name, tvb, pinfo, offset, api_version >= 2, NULL, NULL);

    if (api_version >= 2) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(subti, tvb, offset);

    return offset;
}