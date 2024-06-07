RzCallable *function_type_derive(RzAnalysis *analysis, RZ_NONNULL const char *fcn_name, bool *owned) {
	rz_return_val_if_fail(fcn_name && owned, NULL);
	
	
	
	*owned = false;
	RzCallable *callable = rz_type_func_get(analysis->typedb, fcn_name);
	if (!callable) {
		RzAnalysisFunction *fcn = rz_analysis_get_function_byname(analysis, fcn_name);
		if (!fcn) {
			return NULL;
		}
		callable = rz_analysis_function_derive_type(analysis, fcn);
		if (!callable) {
			return NULL;
		}
		*owned = true;
	}
	return callable;
}