vte_sequence_handler_dc (VteTerminal *terminal, GValueArray *params)
{
	VteScreen *screen;
	VteRowData *rowdata;
	long col;

	screen = terminal->pvt->screen;

	if (_vte_ring_next(screen->row_data) > screen->cursor_current.row) {
		long len;
		
		rowdata = _vte_ring_index_writable (screen->row_data, screen->cursor_current.row);
		g_assert(rowdata != NULL);
		col = screen->cursor_current.col;
		len = _vte_row_data_length (rowdata);
		
		if (col < len) {
			_vte_row_data_remove (rowdata, col);
			if (screen->fill_defaults.attr.back != VTE_DEF_BG) {
				_vte_row_data_fill (rowdata, &screen->fill_defaults, terminal->column_count);
				len = terminal->column_count;
			}
			
			_vte_invalidate_cells(terminal,
					col, len - col,
					screen->cursor_current.row, 1);
		}
	}

	
	terminal->pvt->text_deleted_flag = TRUE;
}