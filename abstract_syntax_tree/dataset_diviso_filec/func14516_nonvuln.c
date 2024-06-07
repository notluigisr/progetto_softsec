RZ_API void rz_core_analysis_coderefs(RzCore *core, ut64 addr) {
	RzAnalysisFunction *fcn = rz_analysis_get_fcn_in(core->analysis, addr, -1);
	if (fcn) {
		const char *me = fcn->name;
		RzListIter *iter;
		RzAnalysisXRef *xref;
		RzList *xrefs = rz_analysis_function_get_xrefs_from(fcn);
		rz_cons_printf("STR", me);
		rz_list_foreach (xrefs, iter, xref) {
			RzFlagItem *item = rz_flag_get_i(core->flags, xref->to);
			const char *dst = item ? item->name : sdb_fmt("STR" PFMT64x, xref->from);
			rz_cons_printf("STR", dst);
			rz_cons_printf("STR", me, dst);
		}
		rz_list_free(xrefs);
	} else {
		eprintf("STR");
	}
}