void flush_hash_page(unsigned long va, real_pte_t pte, int psize, int local)
{
	unsigned long hash, index, shift, hidx, slot;

	DBG_LOW("STR", va);
	pte_iterate_hashed_subpages(pte, psize, va, index, shift) {
		hash = hpt_hash(va, shift);
		hidx = __rpte_to_hidx(pte, index);
		if (hidx & _PTEIDX_SECONDARY)
			hash = ~hash;
		slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot += hidx & _PTEIDX_GROUP_IX;
		DBG_LOW("STR", index, slot, hidx);
		ppc_md.hpte_invalidate(slot, va, psize, local);
	} pte_iterate_hashed_end();
}