static void compactxref(fz_context *ctx, pdf_document *doc, pdf_write_state *opts)
{
	int num, newnum;
	int xref_len = pdf_xref_len(ctx, doc);

	

	newnum = 1;
	for (num = 1; num < xref_len; num++)
	{
		
		if (!opts->use_list[opts->renumber_map[num]])
		{
			opts->renumber_map[num] = 0;
		}
		
		else if (opts->renumber_map[num] == num)
		{
			opts->rev_renumber_map[newnum] = opts->rev_renumber_map[num];
			opts->renumber_map[num] = newnum++;
		}
		
		else
		{
			opts->renumber_map[num] = opts->renumber_map[opts->renumber_map[num]];
		}
	}
}