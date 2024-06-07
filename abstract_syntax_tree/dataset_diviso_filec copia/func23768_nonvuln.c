static inline bool return_type_analysis_context_unresolved(struct ReturnTypeAnalysisCtx *ctx) {
	return !ctx->resolved && ctx->ret_type && ctx->ret_reg;
}