RZ_API void rz_analysis_fcn_vars_cache_fini(RzAnalysisFcnVarsCache *cache) {
	if (!cache) {
		return;
	}
	rz_list_free(cache->bvars);
	rz_list_free(cache->rvars);
	rz_list_free(cache->svars);
}