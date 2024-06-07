pdf_filter_SC_pattern(fz_context *ctx, pdf_processor *proc, const char *name, pdf_pattern *pat, int n, float *color)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_gstate *gstate = gstate_to_update(ctx, p);
	int i;
	fz_strlcpy(gstate->pending.SC.name, name, sizeof gstate->pending.SC.name);
	gstate->pending.SC.pat = pat;
	gstate->pending.SC.shd = NULL;
	gstate->pending.SC.n = n;
	for (i = 0; i < n; ++i)
		gstate->pending.SC.c[i] = color[i];
	copy_resource(ctx, p, PDF_NAME(Pattern), name);
}