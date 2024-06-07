static bool vtable_is_addr_vtable_start_msvc(RVTableContext *context, ut64 curAddress) {
	RAnalRef *xref;
	RListIter *xrefIter;

	if (!curAddress || curAddress == UT64_MAX) {
		return false;
	}
	if (curAddress && !vtable_is_value_in_text_section (context, curAddress, NULL)) {
		return false;
	}
	
	RList *xrefs = r_anal_xrefs_get (context->anal, curAddress);
	if (r_list_empty (xrefs)) {
		r_list_free (xrefs);
		return false;
	}
	r_list_foreach (xrefs, xrefIter, xref) {
		
		if (vtable_addr_in_text_section (context, xref->addr)) {
			ut8 buf[VTABLE_BUFF_SIZE];
			context->anal->iob.read_at (context->anal->iob.io, xref->addr, buf, sizeof(buf));

			RAnalOp analop = {0};
			r_anal_op (context->anal, &analop, xref->addr, buf, sizeof(buf), R_ANAL_OP_MASK_BASIC);

			if (analop.type == R_ANAL_OP_TYPE_MOV
				|| analop.type == R_ANAL_OP_TYPE_LEA) {
				r_list_free (xrefs);
				r_anal_op_fini (&analop);
				return true;
			}

			r_anal_op_fini (&analop);
		}
	}
	r_list_free (xrefs);
	return false;
}