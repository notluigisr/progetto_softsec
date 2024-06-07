dissect_kafka_metadata_request(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                               kafka_api_version_t api_version)
{

    offset = dissect_kafka_array(tree, tvb, pinfo, offset, api_version >= 9, api_version,
                                 &dissect_kafka_metadata_request_topic, NULL);

    if (api_version >= 4) {
        proto_tree_add_item(tree, hf_kafka_allow_auto_topic_creation, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;
    }

    if (api_version >= 8) {
        proto_tree_add_item(tree, hf_kafka_include_cluster_authorized_ops, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;

        proto_tree_add_item(tree, hf_kafka_include_topic_authorized_ops, tvb, offset, 1, ENC_BIG_ENDIAN);
        offset += 1;
    }

    if (api_version >= 9) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, tree, offset, 0);
    }

    return offset;
}