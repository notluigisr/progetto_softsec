static Var* Pe_r_bin_pe_parse_var(struct PE_(r_bin_pe_obj_t)* bin, PE_DWord* curAddr) {
	Var* var = calloc (1, sizeof(*var));
	if (!var) {
		bprintf ("STR");
		return NULL;
	}
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &var->wLength, sizeof(var->wLength)) != sizeof(var->wLength)) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	*curAddr += sizeof(var->wLength);
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &var->wValueLength, sizeof(var->wValueLength)) != sizeof(var->wValueLength)) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	*curAddr += sizeof(var->wValueLength);
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &var->wType, sizeof(var->wType)) != sizeof(var->wType)) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	*curAddr += sizeof(var->wType);
	if (var->wType != 0 && var->wType != 1) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}

	var->szKey = (ut16*) malloc (UT16_ALIGN (TRANSLATION_UTF_16_LEN));  
	if (!var->szKey) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) var->szKey, TRANSLATION_UTF_16_LEN) < 1) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	*curAddr += TRANSLATION_UTF_16_LEN;
	if (memcmp (var->szKey, TRANSLATION_UTF_16, TRANSLATION_UTF_16_LEN)) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	align32 (*curAddr);
	var->numOfValues = var->wValueLength / 4;
	if (!var->numOfValues) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	var->Value = (ut32*) malloc (var->wValueLength);
	if (!var->Value) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) var->Value, var->wValueLength) != var->wValueLength) {
		bprintf ("STR");
		free_Var (var);
		return NULL;
	}
	*curAddr += var->wValueLength;
	return var;
}