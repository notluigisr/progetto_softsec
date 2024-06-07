dissect_dch_timing_advance(proto_tree *tree, packet_info *pinfo,
                           tvbuff_t *tvb, int offset, struct fp_info *p_fp_info)
{
    guint8      cfn;
    guint16     timing_advance;
    proto_item *timing_advance_ti;

    
    cfn = tvb_get_guint8(tvb, offset);
    proto_tree_add_item(tree, hf_fp_cfn_control, tvb, offset, 1, ENC_BIG_ENDIAN);
    offset++;

    
    timing_advance = (tvb_get_guint8(tvb, offset) & 0x3f) * 4;
    timing_advance_ti = proto_tree_add_uint(tree, hf_fp_timing_advance, tvb, offset, 1, timing_advance);
    offset++;

    if ((p_fp_info->release == 7) &&
        (tvb_reported_length_remaining(tvb, offset) > 0)) {

        
        guint8 flags = tvb_get_guint8(tvb, offset);
        guint8 extended_bits = flags & 0x01;
        offset++;

        if (extended_bits) {
            guint8 extra_bit = tvb_get_guint8(tvb, offset) & 0x01;
            proto_item_append_text(timing_advance_ti, "STR",
                                   (timing_advance << 1) | extra_bit);
        }
        offset++;
    }

    col_append_fstr(pinfo->cinfo, COL_INFO, "STR",
                    cfn, timing_advance);

    return offset;
}