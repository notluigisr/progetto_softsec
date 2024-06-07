R_API bool r_anal_var_display(RAnal *anal, RAnalVar *var) {
	char *fmt = r_type_format (anal->sdb_types, var->type);
	RRegItem *i;
	if (!fmt) {
		eprintf ("STR", var->type);
		return false;
	}
	bool usePxr = !strcmp (var->type, "STR"); 
	switch (var->kind) {
	case R_ANAL_VAR_KIND_REG:
		i = r_reg_index_get (anal->reg, var->delta);
		if (i) {
			if (usePxr) {
				anal->cb_printf ("STR", i->name);
			} else {
				anal->cb_printf ("STR", i->name);
			}
		} else {
			eprintf ("STR");
		}
		break;
	case R_ANAL_VAR_KIND_BPV: {
		const st32 real_delta = var->delta + var->fcn->bp_off;
		const ut32 udelta = R_ABS (real_delta);
		const char sign = real_delta >= 0 ? '+' : '-';
		if (usePxr) {
			anal->cb_printf ("STR", anal->reg->name[R_REG_NAME_BP], sign, udelta);
		} else {
			anal->cb_printf ("STR", fmt, anal->reg->name[R_REG_NAME_BP], sign, udelta);
		}
	}
		break;
	case R_ANAL_VAR_KIND_SPV: {
		ut32 udelta = R_ABS (var->delta + var->fcn->maxstack);
		if (usePxr) {
			anal->cb_printf ("STR", anal->reg->name[R_REG_NAME_SP], udelta);
		} else {
			anal->cb_printf ("STR", fmt, anal->reg->name[R_REG_NAME_SP], udelta);
		}
		break;
	}
	}
	free (fmt);
	return true;
}