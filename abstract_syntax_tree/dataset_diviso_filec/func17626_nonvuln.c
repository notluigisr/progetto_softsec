dissect_kafka_sync_group_response(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                  kafka_api_version_t api_version _U_)
{
    if (api_version >= 1) {
        offset = dissect_kafka_throttle_time(tvb, pinfo, tree, offset);
    }

    
    offset = dissect_kafka_error(tvb, pinfo, tree, offset);

    
    if (api_version >= 5) {
        offset = dissect_kafka_compact_string(tree, hf_kafka_protocol_type, tvb, pinfo, offset,
                                              NULL, NULL);
    }

    
    if (api_version >= 5) {
        offset = dissect_kafka_compact_string(tree, hf_kafka_protocol_name, tvb, pinfo, offset,
                                              NULL, NULL);
    }

    
    offset = dissect_kafka_bytes(tree, hf_kafka_member_assignment, tvb, pinfo, offset, api_version >= 4, NULL, NULL);

    if (api_version >= 4) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, tree, offset, 0);
    }

    return offset;
}