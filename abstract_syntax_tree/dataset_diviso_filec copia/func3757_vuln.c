static int mod_instantiate (CONF_SECTION *cs, void **instance)
{
	eap_pwd_t *inst;

	*instance = inst = talloc_zero(cs, eap_pwd_t);
	if (!inst) return -1;

	if (cf_section_parse(cs, inst, pwd_module_config) < 0) {
		return -1;
	}

	if (inst->fragment_size < 100) {
		cf_log_err_cs(cs, "STR");
		return -1;
	}

	if ((inst->bnctx = BN_CTX_new()) == NULL) {
		cf_log_err_cs(cs, "STR");
		return -1;
	}

	return 0;
}