dissect_kafka_write_txn_markers_request_marker(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                                     kafka_api_version_t api_version)
{
    guint64 producer_id;
    proto_item *subti, *subsubti;
    proto_tree *subtree, *subsubtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_marker,
                                     &subti, "STR");

    producer_id = tvb_get_ntoh64(tvb, offset);
    proto_tree_add_item(subtree, hf_kafka_producer_id, tvb, offset, 8, ENC_BIG_ENDIAN);
    offset += 8;

    proto_tree_add_item(subtree, hf_kafka_producer_epoch, tvb, offset, 2, ENC_BIG_ENDIAN);
    offset += 2;

    proto_tree_add_item(subtree, hf_kafka_transaction_result, tvb, offset, 1, ENC_BIG_ENDIAN);
    offset += 1;

    subsubtree = proto_tree_add_subtree(subtree, tvb, offset, -1,
                                     ett_kafka_topics,
                                     &subsubti, "STR");
    offset = dissect_kafka_array(subsubtree, tvb, pinfo, offset, 0, api_version,
                                 &dissect_kafka_write_txn_markers_request_topic, NULL);

    proto_tree_add_item(subsubtree, hf_kafka_coordinator_epoch, tvb, offset, 4, ENC_BIG_ENDIAN);
    offset += 4;

    proto_item_set_end(subsubti, tvb, offset);
    proto_item_set_end(subti, tvb, offset);
    proto_item_append_text(subti, "STR", producer_id);

    return offset;
}