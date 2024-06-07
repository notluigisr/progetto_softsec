dissect_kafka_stop_replica_response(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                    kafka_api_version_t api_version)
{
    
    offset = dissect_kafka_error(tvb, pinfo, tree, offset);

    
    offset = dissect_kafka_array(tree, tvb, pinfo, offset, api_version >= 2, api_version,
                                 &dissect_kafka_stop_replica_response_partition, NULL);

    if (api_version >= 2) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, tree, offset, 0);
    }

    return offset;
}