proto_tree_set_uint64(field_info *fi, guint64 value)
{
	header_field_info *hfinfo;
	guint64		   integer;

	hfinfo = fi->hfinfo;
	integer = value;

	if (hfinfo->bitmask) {
		
		integer &= hfinfo->bitmask;

		
		integer >>= hfinfo_bitshift(hfinfo);

		FI_SET_FLAG(fi, FI_BITS_OFFSET(hfinfo_bitoffset(hfinfo)));
		FI_SET_FLAG(fi, FI_BITS_SIZE(hfinfo_mask_bitwidth(hfinfo)));
	}

	fvalue_set_uinteger64(&fi->value, integer);
}