R_API void r_anal_list_vtables(RAnal *anal, int rad) {
	RVTableContext context;
	r_anal_vtable_begin (anal, &context);

	const char *noMethodName = "STR";
	RVTableMethodInfo *curMethod;
	RListIter *vtableIter;
	RVTableInfo *table;

	RList *vtables = r_anal_vtable_search (&context);

	if (rad == 'j') {
		PJ *pj = pj_new ();
		if (!pj) {
			return;
		}
		pj_a (pj);
		r_list_foreach (vtables, vtableIter, table) {
			pj_o (pj);
			pj_kN (pj, "STR", table->saddr);
			pj_ka (pj, "STR");
			r_vector_foreach (&table->methods, curMethod) {
				RAnalFunction *fcn = r_anal_get_fcn_in (anal, curMethod->addr, 0);
				const char *const name = fcn ? fcn->name : NULL;
				pj_o (pj);
				pj_kN (pj, "STR", curMethod->addr);
				pj_ks (pj, "STR", r_str_get_fail (name, noMethodName));
				pj_end (pj);
			}
			pj_end (pj);
			pj_end (pj);
		}
		pj_end (pj);
		r_cons_println (pj_string (pj));
		pj_free (pj);
	} else if (rad == '*') {
		r_list_foreach (vtables, vtableIter, table) {
			r_cons_printf ("STR",
						   table->saddr,
						   r_anal_vtable_info_get_size (&context, table),
						   table->saddr);
			r_vector_foreach (&table->methods, curMethod) {
				r_cons_printf ("STR", context.word_size, table->saddr + curMethod->vtable_offset);
				RAnalFunction *fcn = r_anal_get_fcn_in (anal, curMethod->addr, 0);
				const char *const name = fcn ? fcn->name : NULL;
				if (name) {
					r_cons_printf ("STR", name, curMethod->addr);
				} else {
					r_cons_printf ("STR", curMethod->addr, curMethod->addr);
				}
			}
		}
	} else {
		r_list_foreach (vtables, vtableIter, table) {
			ut64 vtableStartAddress = table->saddr;
			r_cons_printf ("STR", vtableStartAddress);
			r_vector_foreach (&table->methods, curMethod) {
				RAnalFunction *fcn = r_anal_get_fcn_in (anal, curMethod->addr, 0);
				const char *const name = fcn ? fcn->name : NULL;
				r_cons_printf ("STR", vtableStartAddress, r_str_get_fail (name, noMethodName));
				vtableStartAddress += context.word_size;
			}
			r_cons_newline ();
		}
	}
	r_list_free (vtables);
}