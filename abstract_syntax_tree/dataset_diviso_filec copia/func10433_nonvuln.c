RZ_IPI void rz_core_analysis_function_until(RzCore *core, ut64 addr_end) {
	rz_return_if_fail(core->offset <= addr_end);
	ut64 addr = core->offset;
	int depth = 1;
	ut64 a, b;
	const char *c;
	a = rz_config_get_i(core->config, "STR");
	b = rz_config_get_i(core->config, "STR");
	c = rz_config_get(core->config, "STR");
	rz_config_set_i(core->config, "STR", addr);
	rz_config_set_i(core->config, "STR", addr_end);
	rz_config_set(core->config, "STR");

	RzAnalysisFunction *fcn = rz_analysis_get_fcn_in(core->analysis, addr, 0);
	if (fcn) {
		rz_analysis_function_resize(fcn, addr_end - addr);
	}
	rz_core_analysis_fcn(core, addr, UT64_MAX,
		RZ_ANALYSIS_REF_TYPE_NULL, depth);
	fcn = rz_analysis_get_fcn_in(core->analysis, addr, 0);
	if (fcn) {
		rz_analysis_function_resize(fcn, addr_end - addr);
	}
	rz_config_set_i(core->config, "STR", a);
	rz_config_set_i(core->config, "STR", b);
	rz_config_set(core->config, "STR");
}