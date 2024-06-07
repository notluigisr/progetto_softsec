mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj == NULL)
		
		return;

	if (remove)
	{
		
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(E));
		
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(T));
	}
	
	walk_string(ctx, uni, remove, &tr->alt);
	
	walk_string(ctx, uni, remove, &tr->actualtext);
	
	if (remove)
		remove = (tr->alt.pos == -1 || tr->actualtext.pos == -1);
	else if (tr->alt.pos >= 0 || tr->actualtext.pos >= 0)
	{
		
		remove = 0;
	}
	if (remove)
	{
		
		if (tr->actualtext.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(ActualText));
		if (tr->alt.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(Alt));
		pdf_drop_obj(ctx, tr->mcid_obj);
		tr->mcid_obj = NULL;
		fz_free(ctx, tr->alt.utf8);
		tr->alt.utf8 = NULL;
		fz_free(ctx, tr->actualtext.utf8);
		tr->actualtext.utf8 = NULL;
	}
}