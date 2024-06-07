pdf_filter_h(fz_context *ctx, pdf_processor *proc)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_flush(ctx, p, FLUSH_CTM);
	if (p->chain->op_h)
		p->chain->op_h(ctx, p->chain);
}