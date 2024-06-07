static void relocation_noreturn_process(RzCore *core, RzList *noretl, SetU *todo, RzAnalysisBlock *b, RzBinReloc *rel, ut64 opsize, ut64 addr) {
	RzListIter *iter3;
	char *noret;
	if (rel->import) {
		rz_list_foreach (noretl, iter3, noret) {
			if (!strcmp(rel->import->name, noret)) {
				relocation_function_process_noreturn(core, b, todo, opsize, rel->vaddr, addr);
			}
		}
	} else if (rel->symbol) {
		rz_list_foreach (noretl, iter3, noret) {
			if (!strcmp(rel->symbol->name, noret)) {
				relocation_function_process_noreturn(core, b, todo, opsize, rel->symbol->vaddr, addr);
			}
		}
	}
}