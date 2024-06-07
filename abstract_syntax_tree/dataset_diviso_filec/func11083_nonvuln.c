update_linearization_params(fz_context *ctx, pdf_document *doc, pdf_write_state *opts)
{
	int64_t offset;
	pdf_set_int(ctx, opts->linear_l, opts->file_len);
	
	pdf_set_int(ctx, opts->linear_h0, opts->ofs_list[pdf_xref_len(ctx, doc)-1]);
	
	offset = (opts->start == 1 ? opts->main_xref_offset : opts->ofs_list[1] + opts->hintstream_len);
	pdf_set_int(ctx, opts->linear_h1, offset - opts->ofs_list[pdf_xref_len(ctx, doc)-1]);
	
	pdf_set_int(ctx, opts->linear_o, opts->page_object_lists->page[0]->object[0]);
	
	offset = (opts->start == 1 ? opts->main_xref_offset : opts->ofs_list[1] + opts->hintstream_len);
	pdf_set_int(ctx, opts->linear_e, offset);
	
	pdf_set_int(ctx, opts->linear_n, opts->page_count);
	
	pdf_set_int(ctx, opts->linear_t, opts->first_xref_entry_offset + opts->hintstream_len);
	
	pdf_set_int(ctx, opts->hints_s, opts->hints_shared_offset);
	
	pdf_set_int(ctx, opts->hints_length, opts->hintstream_len);
}