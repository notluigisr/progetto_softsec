static inline bool var_same_kind(RzAnalysisVar *a, RzAnalysisVar *b) {
	return a->kind == b->kind && a->isarg == b->isarg;
}