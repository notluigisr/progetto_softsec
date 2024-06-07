gif_prepare_lzw (GifContext *context)
{
	gint i;

	if (!gif_read (context, &(context->lzw_set_code_size), 1)) {
		
		return -1;
	}
        
        if (context->lzw_set_code_size > MAX_LZW_BITS) {
                g_set_error_literal (context->error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                     _("STR"));
                return -2;
        }

	context->lzw_code_size = context->lzw_set_code_size + 1;
	context->lzw_clear_code = 1 << context->lzw_set_code_size;
	context->lzw_end_code = context->lzw_clear_code + 1;
	context->lzw_max_code_size = 2 * context->lzw_clear_code;
	context->lzw_max_code = context->lzw_clear_code + 2;
	context->lzw_fresh = TRUE;
	context->code_curbit = 0;
	context->code_lastbit = 0;
	context->code_last_byte = 0;
	context->code_done = FALSE;

        g_assert (context->lzw_clear_code <= 
                  G_N_ELEMENTS (context->lzw_table[0]));

	for (i = 0; i < context->lzw_clear_code; ++i) {
		context->lzw_table[0][i] = 0;
		context->lzw_table[1][i] = i;
	}
	for (; i < (1 << MAX_LZW_BITS); ++i)
		context->lzw_table[0][i] = context->lzw_table[1][0] = 0;

	context->lzw_sp = context->lzw_stack;
	gif_set_get_lzw (context);

	return 0;
}