dissect_kafka_update_metadata_request_partition(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree,
                                                      int offset, kafka_api_version_t api_version)
{
    proto_tree *subtree, *subsubtree;
    proto_item *subti, *subsubti;
    int topic_start, topic_len;
    kafka_partition_t partition;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_partition,
                                     &subti, "STR");

    
    if (api_version < 5) {
        offset = dissect_kafka_string(subtree, hf_kafka_topic_name, tvb, pinfo, offset, 0,
                                      &topic_start, &topic_len);
    }

    
    offset = dissect_kafka_int32(subtree, hf_kafka_partition_id, tvb, pinfo, offset, &partition);

    
    offset = dissect_kafka_int32(subtree, hf_kafka_controller_epoch, tvb, pinfo, offset, NULL);

    
    offset = dissect_kafka_int32(subtree, hf_kafka_leader_id, tvb, pinfo, offset, NULL);

    
    offset = dissect_kafka_int32(subtree, hf_kafka_leader_epoch, tvb, pinfo, offset, NULL);

    
    subsubtree = proto_tree_add_subtree(subtree, tvb, offset, -1,
                                        ett_kafka_isrs,
                                        &subsubti, "STR");
    offset = dissect_kafka_array(subsubtree, tvb, pinfo, offset, api_version >= 6, api_version,
                                 &dissect_kafka_update_metadata_request_replica, NULL);
    proto_item_set_end(subsubti, tvb, offset);

    
    offset = dissect_kafka_int32(subtree, hf_kafka_zk_version, tvb, pinfo, offset, NULL);

    
    subsubtree = proto_tree_add_subtree(subtree, tvb, offset, -1,
                                        ett_kafka_replicas,
                                        &subsubti, "STR");
    offset = dissect_kafka_array(subsubtree, tvb, pinfo, offset, api_version >= 6, api_version,
                                 &dissect_kafka_update_metadata_request_replica, NULL);
    proto_item_set_end(subsubti, tvb, offset);

    
    subsubtree = proto_tree_add_subtree(subtree, tvb, offset, -1,
                                        ett_kafka_replicas,
                                        &subsubti, "STR");
    offset = dissect_kafka_array(subsubtree, tvb, pinfo, offset, api_version >= 6, api_version,
                                 &dissect_kafka_update_metadata_request_replica, NULL);
    proto_item_set_end(subsubti, tvb, offset);

    if (api_version >= 6) {
        offset = dissect_kafka_tagged_fields(tvb, pinfo, subtree, offset, 0);
    }

    proto_item_set_end(subti, tvb, offset);

    if (api_version >= 5) {
        proto_item_append_text(subti, "STR",
                               partition);
    } else {
        proto_item_append_text(subti, "STR",
                               tvb_get_string_enc(wmem_packet_scope(), tvb,
                                                  topic_start, topic_len, ENC_UTF_8),
                               partition);
    }
    return offset;
}