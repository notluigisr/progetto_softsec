static int bin_pdb(RCore *core, int mode) {
	R_PDB pdb = R_EMPTY;
	ut64 baddr = r_bin_get_baddr (core->bin);

	pdb.cb_printf = r_cons_printf;
	if (!init_pdb_parser (&pdb, core->bin->file)) {
		return false;
	}
	if (!pdb.pdb_parse (&pdb)) {
		eprintf ("STR");
		pdb.finish_pdb_parse (&pdb);
		return false;
	}
	if (mode == R_CORE_BIN_JSON) {
		r_cons_printf("STR");
	}

	switch (mode) {
	case R_CORE_BIN_SET:
		mode = 's';
		r_core_cmd0 (core, "STR");
		return true;
	case R_CORE_BIN_JSON:
		mode = 'j';
		break;
	case '*':
	case 1:
		mode = 'r';
		break;
	default:
		mode = 'd'; 
		break;
	}

	pdb.print_types (&pdb, mode);
	if (mode == 'j') {
		r_cons_printf ("STR");
	}
	pdb.print_gvars (&pdb, baddr, mode);
	if (mode == 'j') {
		r_cons_printf ("STR");
	}
	pdb.finish_pdb_parse (&pdb);

	return true;
}