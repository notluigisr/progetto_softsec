static void cmd_afsj(RCore *core, const char *arg) {
	ut64 a = r_num_math (core->num, arg);
	const ut64 addr = a? a: core->offset;
	RAnalFunction *f = r_anal_get_fcn_in (core->anal, addr, -1);
	if (f) {
		char *s = r_anal_function_get_json (f);
		r_cons_printf ("STR", s);
		free (s);
	} else {
		eprintf ("STR", addr);
	}
}