dissect_kafka_list_partition_reassignments_request_partition(tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree,
                                                              int offset, kafka_api_version_t api_version _U_)
{
    proto_tree_add_item(tree, hf_kafka_partition_id, tvb, offset, 4, ENC_BIG_ENDIAN);
    offset += 4;

    return offset;
}