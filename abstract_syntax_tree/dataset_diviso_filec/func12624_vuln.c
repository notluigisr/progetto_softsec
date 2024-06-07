lmp_print_data_link_subobjs(netdissect_options *ndo, const u_char *obj_tptr,
                            int total_subobj_len, int offset)
{
    int hexdump = FALSE;
    int subobj_type, subobj_len;

    union { 
        float f;
        uint32_t i;
    } bw;

    while (total_subobj_len > 0 && hexdump == FALSE ) {
	subobj_type = EXTRACT_8BITS(obj_tptr + offset);
	subobj_len  = EXTRACT_8BITS(obj_tptr + offset + 1);
	ND_PRINT((ndo, "STR",
		tok2str(lmp_data_link_subobj,
			"STR",
			subobj_type),
			subobj_type,
			subobj_len));
	if (subobj_len < 4) {
	    ND_PRINT((ndo, "STR"));
	    break;
	}
	if ((subobj_len % 4) != 0) {
	    ND_PRINT((ndo, "STR"));
	    break;
	}
	if (total_subobj_len < subobj_len) {
	    ND_PRINT((ndo, "STR"));
	    break;
	}
	switch(subobj_type) {
	case INT_SWITCHING_TYPE_SUBOBJ:
	    ND_PRINT((ndo, "STR",
		tok2str(gmpls_switch_cap_values,
			"STR",
			EXTRACT_8BITS(obj_tptr + offset + 2)),
			EXTRACT_8BITS(obj_tptr + offset + 2)));
	    ND_PRINT((ndo, "STR",
		tok2str(gmpls_encoding_values,
			"STR",
			EXTRACT_8BITS(obj_tptr + offset + 3)),
			EXTRACT_8BITS(obj_tptr + offset + 3)));
	    bw.i = EXTRACT_32BITS(obj_tptr+offset+4);
	    ND_PRINT((ndo, "STR",
                bw.f*8/1000000));
	    bw.i = EXTRACT_32BITS(obj_tptr+offset+8);
	    ND_PRINT((ndo, "STR",
                bw.f*8/1000000));
	    break;
	case WAVELENGTH_SUBOBJ:
	    ND_PRINT((ndo, "STR",
		EXTRACT_32BITS(obj_tptr+offset+4)));
	    break;
	default:
	    
	    hexdump=TRUE;
	    break;
	}
	total_subobj_len-=subobj_len;
	offset+=subobj_len;
    }
    return (hexdump);
}