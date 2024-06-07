static bool reanalyze_fcns_cb(void *u, const ut64 k, const void *v) {
	RzCore *core = u;
	RzAnalysisFunction *fcn = (RzAnalysisFunction *)(size_t)k;
	if (fcn->addr && analyze_noreturn_function(core, fcn)) {
		fcn->is_noreturn = true;
		rz_analysis_noreturn_add(core->analysis, NULL, fcn->addr);
	}
	return true;
}