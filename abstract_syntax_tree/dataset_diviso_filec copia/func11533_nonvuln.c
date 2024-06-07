dissect_kafka_alter_replica_log_dirs_request(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                    kafka_api_version_t api_version)
{
    proto_item *subti;
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_log_dirs,
                                     &subti, "STR");
    offset = dissect_kafka_array(subtree, tvb, pinfo, offset, 0, api_version,
                                 &dissect_kafka_alter_replica_log_dirs_request_log_dir, NULL);

    proto_item_set_end(subti, tvb, offset);

    return offset;
}