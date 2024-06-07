mark_root(fz_context *ctx, pdf_document *doc, pdf_write_state *opts, pdf_obj *dict)
{
	int i, n = pdf_dict_len(ctx, dict);

	if (pdf_mark_obj(ctx, dict))
		return;

	fz_try(ctx)
	{
		if (pdf_is_indirect(ctx, dict))
		{
			int num = pdf_to_num(ctx, dict);
			opts->use_list[num] |= USE_CATALOGUE;
		}

		for (i = 0; i < n; i++)
		{
			pdf_obj *key = pdf_dict_get_key(ctx, dict, i);
			pdf_obj *val = pdf_dict_get_val(ctx, dict, i);

			if (pdf_name_eq(ctx, PDF_NAME_Pages, key))
				opts->page_count = mark_pages(ctx, doc, opts, val, 0);
			else if (pdf_name_eq(ctx, PDF_NAME_Names, key))
				mark_all(ctx, doc, opts, val, USE_OTHER_OBJECTS, -1);
			else if (pdf_name_eq(ctx, PDF_NAME_Dests, key))
				mark_all(ctx, doc, opts, val, USE_OTHER_OBJECTS, -1);
			else if (pdf_name_eq(ctx, PDF_NAME_Outlines, key))
			{
				int section;
				
				if (pdf_name_eq(ctx, pdf_dict_get(ctx, dict, PDF_NAME_PageMode), PDF_NAME_UseOutlines))
					section = USE_PAGE1;
				else
					section = USE_OTHER_OBJECTS;
				mark_all(ctx, doc, opts, val, section, -1);
			}
			else
				mark_all(ctx, doc, opts, val, USE_CATALOGUE, -1);
		}
	}
	fz_always(ctx)
	{
		pdf_unmark_obj(ctx, dict);
	}
	fz_catch(ctx)
	{
		fz_rethrow(ctx);
	}
}