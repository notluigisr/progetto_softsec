pdf_filter_TJ(fz_context *ctx, pdf_processor *proc, pdf_obj *array)
{
	pdf_filter_processor *p = (pdf_filter_processor*)proc;
	filter_show_text(ctx, p, array);
}