static void writeobject(fz_context *ctx, pdf_document *doc, pdf_write_state *opts, int num, int gen, int skip_xrefs)
{
	pdf_xref_entry *entry;
	pdf_obj *obj;
	pdf_obj *type;

	fz_try(ctx)
	{
		obj = pdf_load_object(ctx, doc, num);
	}
	fz_catch(ctx)
	{
		fz_rethrow_if(ctx, FZ_ERROR_TRYLATER);
		if (opts->continue_on_error)
		{
			fz_write_printf(ctx, opts->out, "STR", num, gen);
			if (opts->errors)
				(*opts->errors)++;
			fz_warn(ctx, "STR", fz_caught_message(ctx));
			return;
		}
		else
			fz_rethrow(ctx);
	}

	
	if (pdf_is_dict(ctx, obj))
	{
		type = pdf_dict_get(ctx, obj, PDF_NAME_Type);
		if (pdf_name_eq(ctx, type, PDF_NAME_ObjStm))
		{
			opts->use_list[num] = 0;
			pdf_drop_obj(ctx, obj);
			return;
		}
		if (skip_xrefs && pdf_name_eq(ctx, type, PDF_NAME_XRef))
		{
			opts->use_list[num] = 0;
			pdf_drop_obj(ctx, obj);
			return;
		}
	}

	entry = pdf_get_xref_entry(ctx, doc, num);
	if (!pdf_obj_num_is_stream(ctx, doc, num))
	{
		fz_write_printf(ctx, opts->out, "STR", num, gen);
		pdf_print_obj(ctx, opts->out, obj, opts->do_tight);
		fz_write_string(ctx, opts->out, "STR");
	}
	else if (entry->stm_ofs < 0 && entry->stm_buf == NULL)
	{
		fz_write_printf(ctx, opts->out, "STR", num, gen);
		pdf_print_obj(ctx, opts->out, obj, opts->do_tight);
		fz_write_string(ctx, opts->out, "STR");
	}
	else
	{
		fz_try(ctx)
		{
			int do_deflate = opts->do_compress;
			int do_expand = opts->do_expand;
			if (opts->do_compress_images && is_image_stream(ctx, obj))
				do_deflate = 1, do_expand = 0;
			if (opts->do_compress_fonts && is_font_stream(ctx, obj))
				do_deflate = 1, do_expand = 0;
			if (is_xml_metadata(ctx, obj))
				do_deflate = 0, do_expand = 0;
			if (do_expand)
				expandstream(ctx, doc, opts, obj, num, gen, do_deflate);
			else
				copystream(ctx, doc, opts, obj, num, gen, do_deflate);
		}
		fz_catch(ctx)
		{
			fz_rethrow_if(ctx, FZ_ERROR_TRYLATER);
			if (opts->continue_on_error)
			{
				fz_write_printf(ctx, opts->out, "STR", num, gen);
				if (opts->errors)
					(*opts->errors)++;
				fz_warn(ctx, "STR", fz_caught_message(ctx));
			}
			else
			{
				pdf_drop_obj(ctx, obj);
				fz_rethrow(ctx);
			}
		}
	}

	pdf_drop_obj(ctx, obj);
}