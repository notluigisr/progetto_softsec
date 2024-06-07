void *MACH0_(mach0_free)(struct MACH0_(obj_t) * mo) {
	if (!mo) {
		return NULL;
	}

	size_t i;
	if (mo->symbols) {
		for (i = 0; !mo->symbols[i].last; i++) {
			free(mo->symbols[i].name);
		}
		free(mo->symbols);
	}
	free(mo->segs);
	free(mo->sects);
	free(mo->symtab);
	free(mo->symstr);
	free(mo->indirectsyms);
	free(mo->imports_by_ord);
	if (mo->imports_by_name) {
		ht_pp_free(mo->imports_by_name);
	}
	free(mo->dyld_info);
	free(mo->toc);
	free(mo->modtab);
	free(mo->libs);
	free(mo->func_start);
	free(mo->signature);
	free(mo->intrp);
	free(mo->compiler);
	if (mo->chained_starts) {
		for (i = 0; i < mo->nchained_starts; i++) {
			if (mo->chained_starts[i]) {
				free(mo->chained_starts[i]->page_start);
				free(mo->chained_starts[i]);
			}
		}
		free(mo->chained_starts);
	}
	rz_pvector_free(mo->patchable_relocs);
	rz_skiplist_free(mo->relocs);
	rz_hash_free(mo->hash);
	rz_buf_free(mo->b);
	free(mo);
	return NULL;
}