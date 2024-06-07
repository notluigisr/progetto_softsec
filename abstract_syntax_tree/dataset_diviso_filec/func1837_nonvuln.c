adjust_for_removed_space(fz_context *ctx, pdf_filter_processor *p)
{
	filter_gstate *gstate = p->gstate;
	float adj = gstate->pending.text.word_space;
	adjust_text(ctx, p, adj * gstate->pending.text.scale, adj);
}