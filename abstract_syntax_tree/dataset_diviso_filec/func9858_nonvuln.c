vte_sequence_handler_ec (VteTerminal *terminal, GValueArray *params)
{
	VteScreen *screen;
	VteRowData *rowdata;
	GValue *value;
	VteCell *cell;
	long col, i, count;

	screen = terminal->pvt->screen;

	
	count = 1;
	if ((params != NULL) && (params->n_values > 0)) {
		value = g_value_array_get_nth(params, 0);
		if (G_VALUE_HOLDS_LONG(value)) {
			count = g_value_get_long(value);
		}
	}

	
	rowdata = _vte_terminal_ensure_row(terminal);
	if (_vte_ring_next(screen->row_data) > screen->cursor_current.row) {
		g_assert(rowdata != NULL);
		
		for (i = 0; i < count; i++) {
			col = screen->cursor_current.col + i;
			if (col >= 0) {
				if (col < (glong) _vte_row_data_length (rowdata)) {
					
					cell = _vte_row_data_get_writable (rowdata, col);
					*cell = screen->color_defaults;
				} else {
					
					_vte_row_data_fill (rowdata, &screen->color_defaults, col);
				}
			}
		}
		
		_vte_invalidate_cells(terminal,
				      screen->cursor_current.col, count,
				      screen->cursor_current.row, 1);
	}

	
	terminal->pvt->text_deleted_flag = TRUE;
}