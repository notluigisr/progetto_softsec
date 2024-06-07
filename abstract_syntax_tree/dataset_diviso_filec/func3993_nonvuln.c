pdf_filter_Tm(fz_context *ctx, pdf_processor *proc, float a, float b, float c, float d, float e, float f)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	pdf_tos_set_matrix(&p->tos, a, b, c, d, e, f);
	p->Tm_pending = 1;
	p->Tm_adjust = 0;
}