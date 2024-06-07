proto_tree_add_item_ret_varint(proto_tree *tree, int hfindex, tvbuff_t *tvb,
    const gint start, gint length, const guint encoding, guint64 *retval, gint *lenretval)
{
	header_field_info *hfinfo = proto_registrar_get_nth(hfindex);
	field_info	*new_fi;
	guint64		value;

	DISSECTOR_ASSERT_HINT(hfinfo != NULL, "STR");

	if ((!IS_FT_INT(hfinfo->type)) && (!IS_FT_UINT(hfinfo->type))) {
		REPORT_DISSECTOR_BUG("STR",
		    hfinfo->abbrev);
	}

	
	
	if (length == 0)
		REPORT_DISSECTOR_BUG("STR",
			length);

	if (encoding & ENC_STRING) {
		REPORT_DISSECTOR_BUG("STR");
	}

	length = tvb_get_varint(tvb, start, (length == -1) ? FT_VARINT_MAX_LEN : length, &value, encoding);

	if (retval) {
		*retval = value;
		if (hfinfo->bitmask) {
			
			*retval &= hfinfo->bitmask;
			
			*retval >>= hfinfo_bitshift(hfinfo);
		}
	}

	if (lenretval) {
		*lenretval = length;
	}

	CHECK_FOR_NULL_TREE(tree);

	TRY_TO_FAKE_THIS_ITEM(tree, hfinfo->id, hfinfo);

	new_fi = new_field_info(tree, hfinfo, tvb, start, length);

	proto_tree_set_uint64(new_fi, value);

	new_fi->flags |= (encoding & ENC_LITTLE_ENDIAN) ? FI_LITTLE_ENDIAN : FI_BIG_ENDIAN;
	if (encoding & (ENC_VARINT_PROTOBUF|ENC_VARINT_ZIGZAG)) {
		new_fi->flags |= FI_VARINT;
	}

	return proto_tree_add_node(tree, new_fi);

}