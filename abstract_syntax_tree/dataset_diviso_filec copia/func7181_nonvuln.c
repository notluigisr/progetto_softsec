dissect_common_timing_advance(packet_info *pinfo, proto_tree *tree, tvbuff_t *tvb, int offset)
{
    guint8  cfn;
    guint16 timing_advance;

    
    cfn = tvb_get_guint8(tvb, offset);
    proto_tree_add_item(tree, hf_fp_cfn_control, tvb, offset, 1, ENC_BIG_ENDIAN);
    offset++;

    
    timing_advance = (tvb_get_guint8(tvb, offset) & 0x3f) * 4;
    proto_tree_add_uint(tree, hf_fp_timing_advance, tvb, offset, 1, timing_advance);
    offset++;

    col_append_fstr(pinfo->cinfo, COL_INFO, "STR",
                    cfn, timing_advance);

    return offset;
}