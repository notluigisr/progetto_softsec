static void cmd_anal_blocks(RCore *core, const char *input) {
	ut64 from , to;
	char *arg = strchr (input, ' ');
	r_cons_break_push (NULL, NULL);
	if (!arg) {
		RList *list = r_core_get_boundaries_prot (core, R_PERM_X, NULL, "STR");
		RListIter *iter;
		RIOMap* map;
		if (!list) {
			goto ctrl_c;
		}
		r_list_foreach (list, iter, map) {
			from = map->itv.addr;
			to = r_itv_end (map->itv);
			if (r_cons_is_breaked ()) {
				goto ctrl_c;
			}
			if (!from && !to) {
				eprintf ("STR");
			} else if (to - from > UT32_MAX) {
				eprintf ("STR");
			} else {
				r_core_cmdf (core, "STR"PFMT64x, (to - from), from);
			}
		}
	} else {
		ut64 sz = r_num_math (core->num, arg + 1);
		r_core_cmdf (core, "STR"PFMT64x, sz, core->offset);
	}
ctrl_c:
	r_cons_break_pop ();
}