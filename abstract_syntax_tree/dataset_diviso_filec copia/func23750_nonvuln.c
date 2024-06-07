pdf_filter_gs_op(fz_context *ctx, pdf_processor *proc, int b)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, 0);
	if (p->chain->op_gs_op)
		p->chain->op_gs_op(ctx, p->chain, b);
}