dissect_kafka_tagged_fields(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, int offset,
                               kafka_api_version_t api_version _U_)
{
    gint64 count;
    guint len;
    proto_item *subti;
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, offset, -1,
                                     ett_kafka_tagged_fields,
                                     &subti, "STR");

    len = tvb_get_varint(tvb, offset, FT_VARINT_MAX_LEN, &count, ENC_VARINT_PROTOBUF);
    if (len == 0) {
        expert_add_info(pinfo, subtree, &ei_kafka_bad_varint);
        return offset;
    }
    offset += len;

    
    offset = dissect_kafka_array_elements(subtree, tvb, pinfo, offset, api_version, &dissect_kafka_tagged_field, (gint32)count);

    proto_item_set_end(subti, tvb, offset);

    return offset;
}